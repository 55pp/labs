-module(plib).

-export([next/1, damage/1, level_done/1, level_fail/0]).

next({Health, Key}) ->
    gen_event:notify(event_logger, {msg, "player: next~n"}),
    gen_server:cast(r_server, {next, Health, Key}).

damage({PHealth, PKey, EHealth}) ->
    gen_event:notify(event_logger, {msg, "player: damage ~n"}),
    gen_server:cast(e_server, {damage, PHealth, PKey, EHealth - 10}).

level_done({Health}) ->
    gen_event:notify(event_logger, {msg, "player: done~n"}),
    gen_server:cast(gm_server, {done, Health}).

level_fail() ->
    gen_event:notify(event_logger, {msg, "player: dead~n"}),
    gen_server:cast(gm_server, {dead}).
