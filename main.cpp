#include <Windows.h>
//#include "auth.hpp"
#include <string>
#include "utils.hpp"
#include "skStr.h"
#include "includes.hpp"
#include "SDK.hpp"
#include "Overwatch.hpp"
#include <io.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);


void MainThread() {
	using namespace OW;
	std::cout << "Launch in Main Menu and go to Practice range..\n";
	while (!SDK->Initialize() || !SDK->GetGlobalKey())
	{
		std::cout << "Waiting..\n";
		Sleep(2000);
	}

	_beginthread((_beginthread_proc_type)entity_scan_thread, 0, 0);
	Sleep(50);
	_beginthread((_beginthread_proc_type)entity_thread, 0, 0);
	_beginthread((_beginthread_proc_type)viewmatrix_thread, 0, 0);
	Sleep(500);
	_beginthread((_beginthread_proc_type)aimbot_thread, 0, 0);
	_beginthread((_beginthread_proc_type)overlay_thread, 0, 0);
	_beginthread((_beginthread_proc_type)configsavenloadthread, 0, 0);
	Sleep(10);
	_beginthread((_beginthread_proc_type)looprpmthread, 0, 0);
	//_beginthread((_beginthread_proc_type)playmusicthread, 0, 0);

	while (FindWindowA(skCrypt("TankWindowClass"), NULL))
	{
		auto viewMatrixVal = SDK->RPM<uint64_t>(SDK->dwGameBase + offset::Address_viewmatrix_base) ^ offset::offset_viewmatrix_xor_key;
		viewMatrixVal = SDK->RPM<uint64_t>(viewMatrixVal + 0x5C0);
		viewMatrixVal = SDK->RPM<uint64_t>(viewMatrixVal + 0x118);
		//mutex.lock();
		viewMatrix_xor_ptr = viewMatrixVal + 0x130;
		//mutex.unlock();
		auto view = SDK->RPM<uint64_t>(SDK->dwGameBase + offset::Address_viewmatrix_base_test) + offset::offset_viewmatrix_ptr;
		//mutex.lock();
		viewMatrixPtr = view;
		//mutex.unlock();
		//viewMatrixPtr = viewMatrix_xor_ptr;

		Sleep(100);
	}
}
/*
	Video on what ownerid and secret are https://youtu.be/uJ0Umy_C6Fg

	Video on how to add KeyAuth to your own application https://youtu.be/GB4XW_TsHqA

	Video to use Web Loader (control loader from customer panel) https://youtu.be/9-qgmsUUCK4
*/

//api KeyAuthApp(name, ownerid, secret, version, url);

int main()
{
	if (!OW::Config::loginornot) MainThread();
	std::string consoleTitle = (std::string)skCrypt("RigelExternal Ver:  ") + compilation_date;
	SetConsoleTitleA(consoleTitle.c_str());
	std::cout << skCrypt("\n\nConnecting to server..");
	//KeyAuthApp.init();

	//if (!KeyAuthApp.data.success)
	//{
		//std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		//Sleep(1500);
		//exit(0);
	//}


	//Optional - check if HWID or IP blacklisted

	/*if (KeyAuthApp.checkblack()) {
		abort();
	}
	*/

	//std::cout << skCrypt("\n\n App data:");
	//std::cout << skCrypt("\n Number of users: ") << KeyAuthApp.data.numUsers;
	//std::cout << skCrypt("\n Number of online users: ") << KeyAuthApp.data.numOnlineUsers;
	//std::cout << skCrypt("\n Number of keys: ") << KeyAuthApp.data.numKeys;
	//std::cout << skCrypt("\n 当前版本: ") << KeyAuthApp.data.version;
	//std::cout << skCrypt("\n Loader Ready. ") << KeyAuthApp.data.version;
	//std::cout << skCrypt("\n Customer panel link: ") << KeyAuthApp.data.customerPanelLink;
	//std::cout << skCrypt("\n Checking session validation status (remove this if causing your loader to be slow)");
	//KeyAuthApp.check();
	//std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
	/*
	if (std::filesystem::exists(".\\test.json")) //change test.txt to the path of your file :smile:
	{
		if (!CheckIfJsonKeyExists(".\\test.json", "username"))
		{
			std::string key = ReadFromJson(".\\test.json", "license");
			//KeyAuthApp.license(key);
			if (!KeyAuthApp.data.success)
			{
				std::remove(".\\test.json");
				std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
				Sleep(1500);
				exit(0);
			}
			std::cout << skCrypt("\nAuto logging in...");
		}
		else
		{
			std::string username = ReadFromJson(".\\test.json", "username");
			std::string password = ReadFromJson(".\\test.json", "password");
			KeyAuthApp.login(username, password);
			if (!KeyAuthApp.data.success)
			{
				std::remove(".\\test.json");
				std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
				Sleep(1500);
				exit(0);
			}
			std::cout << skCrypt("\nSuccess");
		}
		KeyAuthApp.log("Locked.");
	}
	else
	{
		std::string username;
		std::string password;
		std::string key;
		std::cout << skCrypt("\n Input Your Lisence: ");
		std::cin >> key;
		KeyAuthApp.license(key);
		if (!KeyAuthApp.data.success)
		{
			std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
			Sleep(1500);
			exit(0);
		}
		if (username.empty() || password.empty())
		{
			WriteToJson(".\\test.json", "license", key, false, "", "");
			std::cout << skCrypt("Created file.");
		}
		else
		{
			WriteToJson(".\\test.json", "username", username, true, "password", password);
			std::cout << skCrypt("Created file.");
		}


	}
	
	//std::cout << skCrypt("\n用户数据:");
	//std::cout << skCrypt("\n Username: ") << KeyAuthApp.data.username;
	//std::cout << skCrypt("\n IP地址: ") << KeyAuthApp.data.ip;
	//std::cout << skCrypt("\n\n HWID: ") << KeyAuthApp.data.hwid;
	//::cout << skCrypt("\n Activated: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.createdate)));
	//std::cout << skCrypt("\n 上一次登录: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.lastlogin)));
	//std::cout << skCrypt("\n 卡密信息:\n ");

	for (int i = 0; i < KeyAuthApp.data.subscriptions.size(); i++) { // Prompto#7895 was here
		auto sub = KeyAuthApp.data.subscriptions.at(i);
		//std::cout << skCrypt("\n name: ") << sub.name;
		std::cout << skCrypt("Expires: ") << tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
		expiretime = string_to_timet(sub.expiry);
	}

	std::cout << skCrypt("\n Checking..");
	KeyAuthApp.check();
	std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
	*/
#pragma region example functions


	/*
	// download file, change file.exe to whatever you want.
	// remember, certain paths like windows folder will require you to turn on auto run as admin https://stackoverflow.com/a/19617989

	std::vector<std::uint8_t> bytes = KeyAuthApp.download("362906");

	if (!KeyAuthApp.data.success) // check whether file downloaded correctly
	{
		std::cout << skCrypt("\n\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}

	std::ofstream file("file.dll", std::ios_base::out | std::ios_base::binary);
	file.write((char*)bytes.data(), bytes.size());
	file.close();
	*/


	// KeyAuthApp.setvar("discord", "test#0001"); // set the value of user variable 'discord' to 'test#0001'
	// std::string userVar = KeyAuthApp.getvar("discord");
	// if (!KeyAuthApp.data.success) // check whether user variable exists and was retrieved correctly
	// {
	// 	std::cout << skCrypt("\n\n Status: ") << KeyAuthApp.data.message;
	// 	Sleep(1500);
	// 	exit(0);
	// }
	// std::cout << "\n user variable - " + userVar; // get value of the user variable 'discord'

	/*
	// let's say you want to send request to https://keyauth.win/api/seller/?sellerkey=f43795eb89d6060b74cdfc56978155ef&type=black&ip=1.1.1.1&hwid=abc
	// but doing that from inside the loader is a bad idea as the link could get leaked.
	// Instead, you should create a webhook with the https://keyauth.win/api/seller/?sellerkey=f43795eb89d6060b74cdfc56978155ef part as the URL
	// then in your loader, put the rest of the link (the other paramaters) in your loader. And then it will send request from KeyAuth server and return response in string resp

	// example to send normal request with no POST data
	std::string resp = KeyAuthApp.webhook("5iZMT1f1XW", "?mak=best&debug=1");

	// example to send form data
	resp = KeyAuthApp.webhook("5iZMT1f1XW", "", "type=init&ver=1.0&name=test&ownerid=j9Gj0FTemM", "application/x-www-form-urlencoded");

	// example to send JSON
	resp = KeyAuthApp.webhook("5iZMT1f1XW", "", "{\"content\": \"webhook message here\",\"embeds\": null}", "application/json");
	if (!KeyAuthApp.data.success) // check whether webhook request sent correctly
	{
		std::cout << skCrypt("\n\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}
	std::cout << "\n Response recieved from webhook request: " + resp;
	*/

	// get data from global variable with name 'status'
	// std::cout << "\n status - " + KeyAuthApp.var("status");

	// KeyAuthApp.log("user logged in"); // send event to logs. if you set discord webhook in app settings, it will send there instead of dashboard
	// KeyAuthApp.ban(); // ban the current user, must be logged in
	// KeyAuthApp.ban("Don't try to crack my loader, cunt."); // ban the current user (with a reason), must be logged in

	/*
	// allow users to communicate amongst each other with through KeyAuth. Thank you Nuss31#1102 for this C++ implementation
	// send chat messages
	std::cout << skCrypt("\n Type Chat message: ");
	std::string message;
	//getline is important cause cin alone stops captureing after a space
	std::getline(std::cin, message);
	if (!KeyAuthApp.chatsend("test", message))
	{
		std::cout << KeyAuthApp.data.message << std::endl;
	}
	// get chat messages
	KeyAuthApp.chatget("test");
	for (int i = 0; i < KeyAuthApp.data.channeldata.size(); i++)
	{
		std::cout << "\n Author:" + KeyAuthApp.data.channeldata[i].author + " | Message:" + KeyAuthApp.data.channeldata[i].message + " | Send Time:" + tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.channeldata[i].timestamp)));
	}
	*/

	/*
	// change username
	// allow users to change their usernames when logged-in
	std::cout << skCrypt("\n Change Username To: ");
	std::string newusername;
	std::cin >> newusername;
	KeyAuthApp.changeusername(newusername);
	if (KeyAuthApp.data.success)
	{
		std::cout << KeyAuthApp.data.message << std::endl;
	}
	*/
#pragma endregion Example on how to use KeyAuth functions

	using namespace OW;

	bool is_login = false;
	std::string license{};

	std::cout << "Loading functions..\n";
	MainThread();
	Sleep(10000);
	exit(0);
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}