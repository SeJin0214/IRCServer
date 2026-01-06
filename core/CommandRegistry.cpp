

#include "CommandRegistry.hpp"
#include "DirectMessageCommand.hpp"
#include "SendChannelMessageCommand.hpp"
#include "QuitCommand.hpp"
#include "JoinCommand.hpp"
#include "TopicCommand.hpp"
#include "ListCommand.hpp"
#include "ModeCommand.hpp"
#include "PartCommand.hpp"
#include "InviteCommand.hpp"
#include "KickCommand.hpp"
#include "WhoCommand.hpp"
#include "NickCommand.hpp"
#include "PassCommand.hpp"
#include "UserCommand.hpp"

CommandRegistry CommandRegistry::instance;


CommandRegistry& CommandRegistry::getInstance()
{
    return instance;
}

CommandRegistry::CommandRegistry()
{
    {
        loggedInSpaceProviders.insert(std::make_pair("NICK", std::make_shared<NickCommand>()));
        loggedInSpaceProviders.insert(std::make_pair("QUIT", std::make_shared<QuitCommand>()));
    }

    {
        loggedInSpaceExecutors.insert(std::make_pair("PASS", std::make_shared<PassCommand>()));
        loggedInSpaceExecutors.insert(std::make_pair("USER", std::make_shared<UserCommand>()));
        loggedInSpaceExecutors.insert(std::make_pair("NICK", std::make_shared<NickCommand>()));
        loggedInSpaceExecutors.insert(std::make_pair("QUIT", std::make_shared<QuitCommand>()));
    }

    {
        lobbyProviders.insert(std::make_pair("PRIVMSG", std::make_shared<DirectMessageCommand>()));
        lobbyProviders.insert(std::make_pair("QUIT", std::make_shared<QuitCommand>()));
        lobbyProviders.insert(std::make_pair("JOIN", std::make_shared<JoinCommand>()));
        lobbyProviders.insert(std::make_pair("TOPIC", std::make_shared<TopicCommand>()));
        lobbyProviders.insert(std::make_pair("LIST", std::make_shared<ListCommand>()));
    }

    {
        lobbyExecutors.insert(std::make_pair("QUIT", std::make_shared<QuitCommand>()));
        lobbyExecutors.insert(std::make_pair("JOIN", std::make_shared<JoinCommand>()));
    }

    {
        channelProviders.insert(std::make_pair("PRIVMSG", std::make_shared<SendChannelMessageCommand>()));
        channelProviders.insert(std::make_pair("QUIT", std::make_shared<QuitCommand>()));
        channelProviders.insert(std::make_pair("JOIN", std::make_shared<JoinCommand>()));
        channelProviders.insert(std::make_pair("TOPIC", std::make_shared<TopicCommand>()));
        channelProviders.insert(std::make_pair("LIST", std::make_shared<ListCommand>()));
        channelProviders.insert(std::make_pair("MODE", std::make_shared<ModeCommand>()));
        channelProviders.insert(std::make_pair("PART", std::make_shared<PartCommand>()));
        channelProviders.insert(std::make_pair("INVITE", std::make_shared<InviteCommand>()));
        channelProviders.insert(std::make_pair("KICK", std::make_shared<KickCommand>()));
        channelProviders.insert(std::make_pair("WHO", std::make_shared<WhoCommand>()));
    }

    {
        channelExecutors.insert(std::make_pair("QUIT", std::make_shared<QuitCommand>()));
        channelExecutors.insert(std::make_pair("JOIN", std::make_shared<JoinCommand>()));
        channelExecutors.insert(std::make_pair("MODE", std::make_shared<ModeCommand>()));
        channelExecutors.insert(std::make_pair("PART", std::make_shared<PartCommand>()));
        channelExecutors.insert(std::make_pair("KICK", std::make_shared<KickCommand>()));
        channelExecutors.insert(std::make_pair("INVITE", std::make_shared<InviteCommand>()));
        channelExecutors.insert(std::make_pair("TOPIC", std::make_shared<TopicCommand>()));
    }

}

Result<std::shared_ptr<IOutgoingMessageProvider> > CommandRegistry::getProviderInChannel(const std::string& command) const
{
    std::unordered_map<std::string, std::shared_ptr<IOutgoingMessageProvider> >::const_iterator it = channelProviders.find(command);
    if (it == channelProviders.end())
    {
        return Result<std::shared_ptr<IOutgoingMessageProvider> >(std::shared_ptr<IOutgoingMessageProvider>(), false);
    }
    return Result<std::shared_ptr<IOutgoingMessageProvider> >(it->second, true);
}

Result<std::shared_ptr<IOutgoingMessageProvider> > CommandRegistry::getProviderInLoggedInSpace(const std::string& command) const
{
    std::unordered_map<std::string, std::shared_ptr<IOutgoingMessageProvider> >::const_iterator it = loggedInSpaceProviders.find(command);
    if (it == loggedInSpaceProviders.end())
    {
        return Result<std::shared_ptr<IOutgoingMessageProvider> >(std::shared_ptr<IOutgoingMessageProvider>(), false);
    }
    return Result<std::shared_ptr<IOutgoingMessageProvider> >(it->second, true);
}

Result<std::shared_ptr<IOutgoingMessageProvider> > CommandRegistry::getProviderInLobby(const std::string& command) const
{
    std::unordered_map<std::string, std::shared_ptr<IOutgoingMessageProvider> >::const_iterator it = lobbyProviders.find(command);
    if (it == lobbyProviders.end())
    {
        return Result<std::shared_ptr<IOutgoingMessageProvider> >(std::shared_ptr<IOutgoingMessageProvider>(), false);
    }
    return Result<std::shared_ptr<IOutgoingMessageProvider> >(it->second, true);
}

Result<std::shared_ptr<IExecutable> > CommandRegistry::getExecutorInChannel(const std::string& command) const
{
    std::unordered_map<std::string, std::shared_ptr<IExecutable> >::const_iterator it = channelExecutors.find(command);
    if (it == channelExecutors.end())
    {
        return Result<std::shared_ptr<IExecutable> >(std::shared_ptr<IExecutable>(), false);
    }
    return Result<std::shared_ptr<IExecutable> >(it->second, true);
}

Result<std::shared_ptr<IExecutable> > CommandRegistry::getExecutorInLoggedInSpace(const std::string& command) const
{
    std::unordered_map<std::string, std::shared_ptr<IExecutable> >::const_iterator it = loggedInSpaceExecutors.find(command);
    if (it == loggedInSpaceExecutors.end())
    {
        return Result<std::shared_ptr<IExecutable> >(std::shared_ptr<IExecutable>(), false);
    }
    return Result<std::shared_ptr<IExecutable> >(it->second, true);
}

Result<std::shared_ptr<IExecutable> > CommandRegistry::getExecutorInLobby(const std::string& command) const
{
    std::unordered_map<std::string, std::shared_ptr<IExecutable> >::const_iterator it = lobbyExecutors.find(command);
    if (it == lobbyExecutors.end())
    {
        return Result<std::shared_ptr<IExecutable> >(std::shared_ptr<IExecutable>(), false);
    }
    return Result<std::shared_ptr<IExecutable> >(it->second, true);
}
