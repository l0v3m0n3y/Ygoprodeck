#ifndef YGOPRODECK_H
#define YGOPRODECK_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplx.h>
#include <iostream>
#include <string>
#include <vector>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Ygoprodeck {
private:
    std::string api_base = "https://db.ygoprodeck.com/api/v7";
    http_client_config client_config;
    
    http_request create_request(const std::string& endpoint, const std::string& method, const std::string& data = "") {
        http_request request;
        
        if (method == "GET") {
            request.set_method(methods::GET);
        } else if (method == "POST") {
            request.set_method(methods::POST);
        } else if (method == "PUT") {
            request.set_method(methods::PUT);
        } else if (method == "DEL") {
            request.set_method(methods::DEL);
        }
        
        request.set_request_uri(utility::conversions::to_string_t(endpoint));
        
        // Set headers
        request.headers().add(U("Host"), U("db.ygoprodeck.com"));
        request.headers().add(U("Content-Type"), U("application/json"));
        request.headers().add(U("User-Agent"), U("Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0"));
        
        if (!data.empty() && (method == "POST" || method == "PUT")) {
            request.set_body(data);
        }
        
        return request;
    }
    
    std::string build_query_params(const std::map<std::string, std::string>& params) {
        if (params.empty()) return "";
        
        std::string query = "?";
        bool first = true;
        for (const auto& param : params) {
            if (!param.second.empty()) {
                if (!first) query += "&";
                // Кодируем значения параметров
                auto encoded_value = web::uri::encode_data_string(utility::conversions::to_string_t(param.second));
                query += param.first + "=" + utility::conversions::to_utf8string(encoded_value);
                first = false;
            }
        }
        return query;
    }
    
    pplx::task<json::value> make_api_call(const std::string& endpoint, const std::string& method, const std::string& data = "") {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        auto request = create_request(endpoint, method, data);

        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: ") + utility::conversions::to_string_t(std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: ") + utility::conversions::to_string_t(e.what()));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

public:
    Ygoprodeck(){
        client_config.set_validate_certificates(false);
    }

    pplx::task<json::value> card_info(const std::string& name="",const std::string& archetype="",const std::string& attribute="",const std::string& sort="",const std::string& banlist="",const std::string& cardset="",const std::string& race="",const std::string& type="",const std::string& format="",const std::string& linkmarker="",const std::string& misc="",const std::string& staple="",const std::string& startdate="",const std::string& enddate="",const std::string& dateregion="",const std::string& language="", int level=0) {
        std::map<std::string, std::string> params;
        if (!language.empty()) params["language"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(language)));
        if (!dateregion.empty()) params["dateregion"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(dateregion)));
        if (!enddate.empty()) params["enddate"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(enddate)));
        if (!startdate.empty()) params["startdate"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(startdate)));
        if (!staple.empty()) params["staple"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(staple)));
        if (!misc.empty()) params["misc"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(misc)));
        if (!linkmarker.empty()) params["linkmarker"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(linkmarker)));
        if (!format.empty()) params["format"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(format)));
        if (!type.empty()) params["type"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(type)));
        if (!name.empty()) params["name"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(name)));
        if (!race.empty()) params["race"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(race)));
        if (!cardset.empty()) params["cardset"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(cardset)));
        if (!banlist.empty()) params["banlist"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(banlist)));
        if (!sort.empty()) params["sort"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(sort)));
        if (!attribute.empty()) params["attribute"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(attribute)));
        if (!archetype.empty()) params["archetype"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(archetype)));
        if (level>0) params["level"] = std::to_string(level);
        return make_api_call("/cardinfo.php" + build_query_params(params),"GET");
    }

    pplx::task<json::value> random_card() {
        return make_api_call("/randomcard.php","GET");
    }

    pplx::task<json::value> get_cardsets() {
        return make_api_call("/cardsets.php","GET");
    }

    pplx::task<json::value> cardsets_info(const std::string& setcode) {
        return make_api_call("/cardsetsinfo.php?setcode=" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(setcode))),"GET");
    }

    pplx::task<json::value> arche_types() {
        return make_api_call("/archetypes.php.","GET");
    }

    pplx::task<json::value> database_version() {
        return make_api_call("/checkDBVer.php","GET");
    }
};
#endif
