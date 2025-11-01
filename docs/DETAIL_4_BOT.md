
## 봇

IRC에서 작동하는 봇을 만들어야 합니다. 기능은 디스코드의 봇과 비슷합니다.  

게임을 좋아하기에 오락기능을 넣어주었으며 명령어 다음과 같습니다.  
1. !help : 사용가능한 명령어와 개발자의 정보를 보여줍니다.  
2. !coinflip : 동전의 앞, 뒤가 랜덤으로 등장합니다.  
3. !dice : 주사위 숫자 1~6까지 랜덤으로 등장합니다.    
  

<br>
<details>
    <summary>봇 생성 및 로그인</summary>
<br>

열려있는 서버에 connect를 요청합니다.  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L29-L49
<br>
<br>
필요한 로그인 정보를 stream에 담아 전송합니다.  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L51-L59
<br>

일정 시간까지 로그인 시도를 합니다.  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L66-L68
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L101
<br>

001 성공 코드를 받는다면, Bot을 실행합니다.  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L95-L99
<br>

</details>
<br>

<details>
    <summary>봇 채널 접속</summary>

<br>

실행 로직은 Server와 비슷합니다.  
세그먼트가 들어오면 Command를 처리합니다.  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L105
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L128
<br>

다른 점은 일정시간마다 채널을 확인하여 입장합니다. 
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L134-L140
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L277-L280

채널 확인도 명령어기 때문에 세그먼트를 수신합니다.  
수신한 세그먼트를 파싱하여 존재하는 채널 목록을 가져옵니다.   
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L206-L222

Bot이 접속한 채널인지 파악하고  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L225-L245

만약 접속하지 않았다면 접속을, 방에 Bot만 남았다면 퇴장을 합니다.  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L247-L254

</details>
<br>

<details>
    <summary>봇 명령 수행</summary>

봇은 채널에 접속했기 때문에 유저의 채팅을 수신하게 됩니다.  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L154

채팅이라면, 명령어인지 확인하고 맞다면 로직을 실행하고 서버로 전송합니다.  
https://github.com/SeJin0214/IRCServer/blob/f76751beab8a610e79597646ed4c6dcfa2a428ba/bot/Bot.cpp#L156-L206

<br>
</details>


### 실행

\$ make   
\$ ./bot < PORT_NUMBER > < SERVER_PASSWORD > < NICKNAME > < USERNAME >

// 실행 영상