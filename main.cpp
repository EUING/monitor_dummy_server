#include <iostream>
#include <vector>

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

int main() {
	std::wcin.imbue(std::locale("Korean"));
	std::wcout.imbue(std::locale("Korean"));
	std::wcerr.imbue(std::locale("Korean"));
	std::wclog.imbue(std::locale("Korean"));

	web::http::experimental::listener::http_listener_config config;
	config.set_timeout(utility::seconds(10));

	web::http::experimental::listener::http_listener listener(U("http://localhost:8080"), config);

	listener.support(web::http::methods::DEL, [](web::http::http_request message) {
		std::vector<utility::string_t> path = web::uri::split_path(web::uri::decode(message.relative_uri().path()));
		auto size = path.size();

		if (size >= 3 && path[0] == U("item") && path[1] == U("info")) {
			utility::string_t path_variable;
			for (int i = 2; i < size; ++i) {
				path_variable.append(path[i]);
				path_variable.push_back(U('/'));
			}

			path_variable.pop_back();

			std::wcout << U("DEL ") << path_variable << std::endl;
			message.reply(web::http::status_codes::OK);
		}
		else {
			message.reply(web::http::status_codes::NotFound);
		}		
	});

	listener.support(web::http::methods::PUT, [](web::http::http_request message) {
		std::vector<utility::string_t> path = web::uri::split_path(web::uri::decode(message.relative_uri().path()));
		auto size = path.size();

		if (size >= 3 && path[0] == U("item") && path[1] == U("info")) {
			utility::string_t path_variable;
			for (int i = 2; i < size; ++i) {
				path_variable.append(path[i]);
				path_variable.push_back(U('/'));
			}

			path_variable.pop_back();

			std::wcout << U("PUT ") << path_variable << std::endl;
			message.reply(web::http::status_codes::OK);
		}
		else {
			message.reply(web::http::status_codes::NotFound);
		}
	});

	listener.support(web::http::methods::PATCH, [](web::http::http_request message) {
		std::vector<utility::string_t> path = web::uri::split_path(web::uri::decode(message.relative_uri().path()));
		auto size = path.size();

		if (size >= 3 && path[0] == U("item") && path[1] == U("name")) {
			utility::string_t path_variable;
			for (int i = 2; i < size; ++i) {
				path_variable.append(path[i]);
				path_variable.push_back(U('/'));
			}

			path_variable.pop_back();

			std::wcout << U("PATCH ") << path_variable << std::endl;
			message.reply(web::http::status_codes::OK);
		}
		else if (size >= 3 && path[0] == U("item") && path[1] == U("info")) {
			utility::string_t path_variable;
			for (int i = 2; i < size; ++i) {
				path_variable.append(path[i]);
				path_variable.push_back(U('/'));
			}

			path_variable.pop_back();

			std::wcout << U("PATCH ") << path_variable << std::endl;
			message.reply(web::http::status_codes::OK);
		}
		else {
			message.reply(web::http::status_codes::NotFound);
		}	
	});

	listener.open().wait();

	wchar_t c = L'\0';
	while (std::wcin >> c) {

	}

	listener.close();

	return 0;
}