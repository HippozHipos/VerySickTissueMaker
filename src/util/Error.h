#pragma once
#include <vector>
#include <string>

namespace vstm {

	class Error
	{
	public:
		enum
		{
			WINDOW_CONSTRUCTION_FAILED
		};

	public:
		Error(int errorCode, const std::string& desc);

	public:
		int Errorcode();
		std::string What();

	private:
		int errorCode;
		std::string what;
	};

	class ErrorHandler
	{
	public:
		enum Action
		{
			TerminateApplication
		};
	private:
		ErrorHandler() = default;

	public:
		static void AddError(int errorCode, const std::string& desc);
		static void Handle();
		static size_t NumActions();
		static Action GetAction(size_t i);

	private:
		//handle specific errors.
		//TODO: Make an event system. If window construction fails, we can sent a close application
		//event.
		static void WindowConstructionFailed();

	private:
		//keep track of all the errors in a single frame
		static std::vector<Error> m_errors;
		static std::vector<Action> m_actions;
	};

}