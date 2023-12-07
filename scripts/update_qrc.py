import os
import xml.etree.ElementTree as ET
from xml.dom import minidom
import re

extensions = ['.qml', '.png', '.ttf', '.otf']

def find_files(directory, extensions, sub_directories=None):
    for dir in sub_directories:
        for root, dirs, files in os.walk(directory + '/' + dir):
            for file in files:
                if any(file.endswith(ext) for ext in extensions):
                    yield os.path.relpath(os.path.join(root, file), directory)

def read_paths_from_qrc(qrc_file):
    if not os.path.exists(qrc_file):
        return set()

    tree = ET.parse(qrc_file)
    root = tree.getroot()

    paths = []

    for qresource in root.findall('qresource'):
        prefix = qresource.get('prefix')
        for file in qresource.findall('file'):
            paths.append(os.path.join(prefix, file.text))

    return set(paths)

def add_files_to_qrc(qrc_file, files, added_paths, qml_files, resource_files):
    if not os.path.exists(qrc_file):
        root = ET.Element('RCC')
        root.set('version', '1.0')
        tree = ET.ElementTree(root)
        tree.write(qrc_file)

    tree = ET.parse(qrc_file)
    root = tree.getroot()

    qresources = {}

    for file in files:
        dir_path = os.path.dirname(file)
        if dir_path not in qresources:
            qresource = ET.Element('qresource')
            qresource.set('prefix', dir_path)
            qresources[dir_path] = qresource
        else:
            qresource = qresources[dir_path]
        file_element = ET.Element('file')
        file_element.text = os.path.basename(file)
        if file in added_paths:
            continue
        for existing_file in qresource.findall('file'):
            if existing_file.text == os.path.basename(file):
                continue
        qresource.append(file_element)
        added_paths.add(file)
        if file.endswith('.qml'):
            qml_files.add(file)
        elif file.endswith('.png') or file.endswith('.ttf') or file.endswith('.otf'):
            resource_files.add(file)

    for qresource in qresources.values():
        root.append(qresource)

    xml_str = ET.tostring(root, 'utf-8')
    parsed_xml = minidom.parseString(xml_str)
    pretty_xml_str = parsed_xml.toprettyxml(indent="\t")
    with open(qrc_file, 'w') as f:
        f.write(pretty_xml_str)

    with open(qrc_file, 'r') as f:
        file_content = f.read()
    file_content = re.sub(r'\n\t+(?!<)(?!\t)', r'', file_content)
    file_content = re.sub('\n{2,}', '\n', file_content)
    with open(qrc_file, 'w') as f:
        f.write(file_content)

    return added_paths, qml_files, resource_files

def remove_duplicate_prefixes(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()

    qresources = {}

    for qresource in root.findall('qresource'):
        prefix = qresource.get('prefix')
        if prefix not in qresources:
            qresources[prefix] = qresource
        else:
            root.remove(qresource)

    tree.write(xml_file)

def print_resources_from_qrc(qrc_file):
    tree = ET.parse(qrc_file)
    root = tree.getroot()

    qml_files = []
    resource_files = []

    for qresource in root.findall('qresource'):
        prefix = qresource.get('prefix')
        for file_element in qresource.findall('file'):
            file = prefix + '/' + file_element.text
            if file.endswith('.qml'):
                qml_files.append(file)
            elif file.endswith('.png') or file.endswith('.ttf') or file.endswith('.otf'):
                resource_files.append(file)
    return (qml_files, resource_files)

def print_sets(qml_files, resource_files):
    print('''qt_add_qml_module(${ProjectName}
   URI main
   VERSION 1.0''')
    print('\tQML_FILES')
    for file in qml_files:
        print(f'\t\t"{file}"')
    print('\n\tRESOURCES')
    for file in resource_files:
        print(f'\t\t"{file}"')
    print('''\tRESOURCE_PREFIX /
\tRESOURCES resources.qrc
)''')

directory = '/Users/full-hat/Documents/MyProjects/BankApp'
sub_directories = ['frontend']
qrc_file = '/Users/full-hat/Documents/MyProjects/BankApp/resources.qrc'

added_paths = read_paths_from_qrc(qrc_file)
files = find_files(directory, extensions, sub_directories)
added_paths, qml_files, resource_files = add_files_to_qrc(qrc_file, files, added_paths, set(), set())
remove_duplicate_prefixes(qrc_file)
all_files = print_resources_from_qrc(qrc_file)
print_sets(*all_files)
