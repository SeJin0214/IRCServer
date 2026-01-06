#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "IOutgoingMessageProvider.hpp"
#include "IExecutable.hpp"
#include "Result.hpp"


class CommandRegistry
{

public:
    static CommandRegistry& getInstance();
    
    CommandRegistry(const CommandRegistry& other) = delete;
    CommandRegistry& operator=(const CommandRegistry& rhs) = delete;

    Result<std::shared_ptr<IOutgoingMessageProvider> > getProviderInChannel(const std::string& command) const;
    Result<std::shared_ptr<IOutgoingMessageProvider> > getProviderInLoggedInSpace(const std::string& command) const;
    Result<std::shared_ptr<IOutgoingMessageProvider> > getProviderInLobby(const std::string& command) const;

    Result<std::shared_ptr<IExecutable> > getExecutorInChannel(const std::string& command) const;
    Result<std::shared_ptr<IExecutable> > getExecutorInLoggedInSpace(const std::string& command) const;
    Result<std::shared_ptr<IExecutable> > getExecutorInLobby(const std::string& command) const;

private:
    static CommandRegistry instance;
    
    std::unordered_map<std::string, std::shared_ptr<IOutgoingMessageProvider> > channelProviders;
    std::unordered_map<std::string, std::shared_ptr<IOutgoingMessageProvider> > loggedInSpaceProviders;
    std::unordered_map<std::string, std::shared_ptr<IOutgoingMessageProvider> > lobbyProviders;

    std::unordered_map<std::string, std::shared_ptr<IExecutable> > channelExecutors;
    std::unordered_map<std::string, std::shared_ptr<IExecutable> > loggedInSpaceExecutors;
    std::unordered_map<std::string, std::shared_ptr<IExecutable> > lobbyExecutors;

    CommandRegistry();
    ~CommandRegistry() = default;
};
