-module(ilib).

-export([start/0, level_complited/1, level_failed/0]).

start() ->
    gen_event:notify(event_logger, {msg, "init: start~n"}),
    gen_server:cast(gm_server, {i_start}).

level_complited(Score) ->
    gen_event:notify(event_logger, {msg, "init: level complited - ~p~n", [Score]}),
    Score.

level_failed() ->
    gen_event:notify(event_logger, {msg, "init: level failed~n"}),
    -1.
