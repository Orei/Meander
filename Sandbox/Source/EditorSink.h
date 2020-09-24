#pragma once
#include <spdlog/details/circular_q.h>
#include <spdlog/details/log_msg_buffer.h>
#include <spdlog/sinks/base_sink.h>
#include <imgui/imgui.h>

namespace Sandbox
{
    struct ConsoleMessage
	{
		spdlog::level::level_enum Level;
		std::string Text;
	};
	
	class EditorSink : public spdlog::sinks::base_sink<std::mutex>
	{
	public:
        explicit EditorSink(size_t maxMessages)
	        : m_MsgBuffer(maxMessages)
        {
        	set_pattern("[%L %H:%M:%S] %v");
        }

		ImVec4 GetLevelColor(const spdlog::level::level_enum& level)
        {
        	switch (level)
        	{
        	default:
        	case spdlog::level::trace:
        		return { 0.8f, 0.8f, 0.8f, 1.f };
        	case spdlog::level::info:
				return { 0.52f, 0.77f, 0.43f, 1.f };
        	case spdlog::level::warn:
				return { 0.9f, 0.77f, 0.19f, 1.f };
        	case spdlog::level::err:
        		return { 1.f, 0.34f, 0.28f, 1.f };
        	case spdlog::level::debug:
				return { 0.8f, 0.2f, 0.8f, 1.f };
        	}
        }

		std::vector<spdlog::details::log_msg_buffer> GetRaw(size_t limit = 0)
		{
		    std::lock_guard<std::mutex> lock(base_sink<std::mutex>::mutex_);
		    size_t numItems = (limit > 0) ? std::min(limit, m_MsgBuffer.size()) : m_MsgBuffer.size();

        	std::vector<spdlog::details::log_msg_buffer> messages;
		    messages.reserve(numItems);
        	
		    for (size_t i = 0; i < numItems; ++i)
		        messages.push_back(m_MsgBuffer.at(i));
        	
		    return messages;
		}

		std::vector<ConsoleMessage> GetFormatted(size_t limit = 0)
	    {
	        std::lock_guard<std::mutex> lock(base_sink<std::mutex>::mutex_);
	        size_t numItems = (limit > 0) ? std::min(limit, m_MsgBuffer.size()) : m_MsgBuffer.size();

        	std::vector<ConsoleMessage> messages;
	        messages.reserve(numItems);
        	
	        for (size_t i = 0; i < numItems; ++i)
	        {
        		spdlog::memory_buf_t formatted;
	        	spdlog::details::log_msg_buffer buffer = m_MsgBuffer.at(i);
        		base_sink<std::mutex>::formatter_->format(buffer, formatted);

	        	messages.push_back({ buffer.level, fmt::to_string(formatted) });
	        }
        	
	        return messages;
	    }

		size_t NumMessages() const { return m_MsgBuffer.size(); }
		
	protected:
		spdlog::details::circular_q<spdlog::details::log_msg_buffer> m_MsgBuffer;

		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			m_MsgBuffer.push_back(spdlog::details::log_msg_buffer(msg));
		}

		void flush_() override { }
	};	
};