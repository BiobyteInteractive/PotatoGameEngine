#pragma once
#ifndef INSTRUMENTOR_H
#define INSTRUMENTOR_H

#include <chrono>
#include <fstream>
#include <string>

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
public:
    Instrumentor();

    void BeginSession(const std::string& name, const std::string& filepath = "results.json");
    void EndSession();
    void WriteProfile(const ProfileResult& result);
    void WriteHeader();
    void WriteFooter();
    static Instrumentor& Get();
};

class InstrumentationTimer
{
public:
    InstrumentationTimer(const char* name);
    ~InstrumentationTimer();
    void Stop();
private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};

#endif