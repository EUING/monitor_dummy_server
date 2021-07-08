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
	listener.support(web::http::methods::GET, [](web::http::http_request message) {
		std::vector<utility::string_t> path = web::uri::split_path(web::uri::decode(message.relative_uri().path()));
		auto size = path.size();

		if (size == 2 && path[0] == U("item") && path[1] == U("contain")) {
			std::wcout << U("GET ") << "root" << std::endl;

			web::json::value object = web::json::value::object();
			object[U("name")] = web::json::value::string(U("1_1"));
			object[U("size")] = web::json::value::number(-1);
			object[U("hash")] = web::json::value::string(U(""));

			web::json::value root = web::json::value::array();
			root[0] = object;

			object[U("name")] = web::json::value::string(U("1_2"));
			root[1] = object;

			object[U("name")] = web::json::value::string(U("1_3"));
			root[2] = object;

			object[U("name")] = web::json::value::string(U("1_4"));
			root[3] = object;
			
			message.reply(web::http::status_codes::OK, root);
		}
		else if (size >= 3 && path[0] == U("item") && path[1] == U("contain")) {
			utility::string_t path_variable;
			for (int i = 2; i < size; ++i) {
				path_variable.append(path[i]);
				path_variable.push_back(U('/'));
			}
			path_variable.pop_back();

			web::json::value root = web::json::value::array();
			web::json::value object = web::json::value::object();

			if (path_variable == L"1_1") {
				object[U("name")] = web::json::value::string(U("1_1_1"));
				object[U("size")] = web::json::value::number(-1);
				object[U("hash")] = web::json::value::string(U(""));				
			}
			else if (path_variable == L"1_2") {
				object[U("name")] = web::json::value::string(U("1_2_1"));
				object[U("size")] = web::json::value::number(-1);
				object[U("hash")] = web::json::value::string(U(""));
			}
			else if (path_variable == L"1_3") {
				object[U("name")] = web::json::value::string(U("1_3_1"));
				object[U("size")] = web::json::value::number(-1);
				object[U("hash")] = web::json::value::string(U(""));
			}
			else if (path_variable == L"1_4") {
				object[U("name")] = web::json::value::string(U("1_4_1"));
				object[U("size")] = web::json::value::number(-1);
				object[U("hash")] = web::json::value::string(U(""));
			}
			else if (path_variable == L"1_1/1_1_1") {
				object[U("name")] = web::json::value::string(U("1_1_1_1.txt"));
				object[U("size")] = web::json::value::number(0);
				object[U("hash")] = web::json::value::string(U("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"));
			}
			else if (path_variable == L"1_2/1_2_1") {
				object[U("name")] = web::json::value::string(U("1_2_1_1.txt"));
				object[U("size")] = web::json::value::number(0);
				object[U("hash")] = web::json::value::string(U("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"));
			}
			else if (path_variable == L"1_3/1_3_1") {
				object[U("name")] = web::json::value::string(U("1_3_1_1.txt"));
				object[U("size")] = web::json::value::number(0);
				object[U("hash")] = web::json::value::string(U("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"));
			}
			else if (path_variable == L"1_4/1_4_1") {
				object[U("name")] = web::json::value::string(U("1_4_1_1.txt"));
				object[U("size")] = web::json::value::number(0);
				object[U("hash")] = web::json::value::string(U("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"));
			}

			root[0] = object;

			std::wcout << U("GET ") << path_variable << std::endl;
			message.reply(web::http::status_codes::OK, root);
		}
		else {
			message.reply(web::http::status_codes::NotFound);
		}
	});

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

		if (size >= 3 && path[0] == U("item") && path[1] == U("info")) {
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