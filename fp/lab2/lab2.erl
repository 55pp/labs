

-module(lab2_1).
-author('tester@testerPC').
-export([expr/1, expr_2/1, main_p/0, gm_p/0, e_p/0, r_p/0, p_p/0]).

expr([]) ->
    0;
expr([H | []]) ->
    H;
expr(["+", H1, H2]) ->
    expr(H1) + expr(H2);
expr(["-", H1, H2]) ->
    expr(H1) - expr(H2);
expr(["*", H1, H2]) ->
    expr(H1) * expr(H2);
expr(["/", H1, H2]) ->
    expr(H1) / expr(H2);
expr(E) ->
    E.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

expr_2(L) ->
    Self = self(),
    wait_for(spawn(fun() -> expr_p(L, Self) end)).

wait_for(Pid) ->
    receive
	{Pid, Res} ->
	    Res
    end.

expr_p([], Pid) ->
    Pid ! {self(), 0};
expr_p([H | []], Pid) ->
    Pid ! {self(), H};
expr_p(["+", H1, H2], Pid) ->
    Self = self(),
    wait_for("+", spawn(fun() -> expr_p(H1, Self) end), spawn(fun() -> expr_p(H2, Self) end), Pid, 0, 0);
expr_p(["-", H1, H2], Pid) ->
    Self = self(),
    wait_for("-", spawn(fun() -> expr_p(H1, Self) end), spawn(fun() -> expr_p(H2, Self) end), Pid, 0, 0);
expr_p(["*", H1, H2], Pid) ->
    Self = self(),
    wait_for("*", spawn(fun() -> expr_p(H1, Self) end), spawn(fun() -> expr_p(H2, Self) end), Pid, 0, 0);
expr_p(["/", H1, H2], Pid) ->
    Self = self(),
    wait_for("/", spawn(fun() -> expr_p(H1, Self) end), spawn(fun() -> expr_p(H2, Self) end), Pid, 0, 0);
expr_p(E, Pid) ->
    Pid ! {self(), E}.

wait_for(O, 0, 0, ParentPid, O1, O2) ->
    ParentPid ! {self(), calc(O, O1, O2)};
wait_for(O, Pid1, Pid2, ParentPid, O1, O2) ->
    receive
	{Pid1, I1} -> 
	    wait_for(O, 0, Pid2, ParentPid, I1, O2);
	{Pid2, I2} -> 
	    wait_for(O, Pid1, 0, ParentPid, O1, I2)
    end.

calc("+", O1, O2) ->
    (O1 + O2);
calc("-", O1, O2) ->
    (O1 - O2);
calc("*", O1, O2) ->
    (O1 * O2);
calc("/", O1, O2) ->
    (O1 / O2).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

wait(NodeFullName, NodeName, undefined) ->
    wait(NodeFullName, NodeName, global:whereis_name(NodeName));
wait(NodeFullName, NodeName, pang) ->
    wait(NodeFullName, NodeName, net_adm:ping(NodeFullName));
wait(NodeFullName, NodeName, pong) ->
    wait(NodeFullName, NodeName, undefined);
wait(_NodeFullName, _NodeName, Pid) ->
    Pid.
    

main_p() ->
    io:format("start~n"),
    global:register_name(main, spawn(fun() -> main_s() end)),
    ManagerPid = wait('manager@testerPC', manager, pang),
    ManagerPid ! {m_start, self()},
    io:format("~p~n", [self()]),
    main_s().

main_s() ->
    receive
	{_GmPid, done, Score} ->
	    Score
    end.

gm_p() ->
    global:register_name(manager, spawn(fun() -> gm_w() end)).

gm_w() ->
    io:format("------------~n", []),
    PlayerPid = wait('player@testerPC', player, pang),
    receive
	{m_start, MainPid} ->
	    io:format("send start to player~n", []),
	    PlayerPid ! {gm_start, self()},
	    gm_s(PlayerPid, MainPid)
    end,
    gm_w().

gm_s(_PlayerPid, MainPid) ->
    receive

	{die} -> 
	    io:format("gm die~n"),
	    MainPid ! {self(), done, 0};

	{done, HP} -> 
	    io:format("gm done~n"),
	    MainPid ! {self(), done, HP}
    end.    

r_p() ->
    global:register_name(roll, spawn(fun() -> r_w() end)).

r_w() ->
    PlayerPid = wait('player@testerPC', player, pang),
    receive
	{next} ->
	    io:format("roll~n", []),
	    roll(PlayerPid, rand:uniform(3))
	end,
    r_w().

roll(PlayerPid, 1) ->
    io:format("roll 1~n"),
    PlayerPid ! {health, 50};
roll(PlayerPid, 2) ->
    io:format("roll 2~n"),
    PlayerPid ! {key, 1};
roll(PlayerPid, 3) ->
    io:format("roll 3~n"),
    wait('enemy@testerPC', enemy, pang) ! {atack, PlayerPid, 30}.


p_p() ->
    global:register_name(player, spawn(fun() -> p_w() end)).

p_w() ->
    RollPid = wait('roll@testerPC', roll, pang),
    io:format("wait roll~n", []),
    receive
	{gm_start, GmPid} ->
	    RollPid ! {next},
	    p_s(100, 0, GmPid, RollPid)
    end,
    p_w().

p_s(0, _Key, GmPid, _RollPid) ->
    GmPid ! {die};
p_s(HP, 3, GmPid, _RollPid) ->
    GmPid ! {done, HP};
p_s(HP, Key, GmPid, RollPid) ->
    receive
	{EnemyPid, damage, Damage} ->
	    io:format("player: damage~n"),
	    EnemyPid ! {self(), damage, 10},
	    p_s(HP - Damage, Key, GmPid, RollPid);
	{health, Health} ->
	    io:format("player: health~n"),
	    RollPid ! {next},
	    p_s(HP + Health, Key, GmPid, RollPid);
	{key, One} ->
	    io:format("player: key~n"),
	    RollPid ! {next},
	    p_s(HP, Key + One, GmPid, RollPid);
	{die} ->
	    io:format("player: die~n"),
	    RollPid ! {next},
	    p_s(HP, Key, GmPid, RollPid)
    end.

e_p() ->
    global:register_name(enemy, spawn(fun() -> e_w() end)).

e_w() ->
    io:format("-------------~n", []),
    receive
	{atack, PlayerPid, HP} ->
	    PlayerPid ! {self(), damage, 10},
	    e_s(PlayerPid, HP)
    end,
    e_w().

e_s(PlayerPid, 0) ->
    PlayerPid ! {die};
e_s(PlayerPid, HP) ->
    receive
	{PlayerPid, damage, Damage} ->
	    io:format("enemy: damage~n"),
	    PlayerPid ! {self(), damage, 10},
	    e_s(PlayerPid, HP - Damage)
    end.
