//
// Created by Full-Hat on 11/12/2023.
//
#pragma once

#include "backend/Api.hpp"

class TestApi : public backend::Api {
public:
    [[nodiscard]]
    virtual resp_accounts_get AccountsGet(const QString &token) override {
        return {
            200,
            {
                    {
                        "name",
                        "number",
                        1.0,
                        true
                    },
                    {
                        "Number1",
                        "name1",
                        2.0,
                        true
                    }
            }
        };
    }

    virtual resp_cards_get CardsGet(const QString &token) override {
        return {
                200,
                {
                        {
                                "name",
                                "number",
                                "date",
                                true
                        },
                        {
                                "Number1",
                                "name1",
                                "date1",
                                true
                        }
                }
        };
    }
};
