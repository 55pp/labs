-module(gmlib).

-export([start/0, end_level/0, end_level/1]).

start() ->
    gen_event:notify(event_logger, {msg, "gm: start~n"}),
    gen_server:cast(p_server, {gm_start, 100, 0}),
    ok.

end_level({Score}) ->
    gen_event:notify(event_logger, {msg, "gm: level done~n"}),
    gen_server:cast(i_server, {gm_done, Score}).
end_level() ->
    gen_event:notify(event_logger, {msg, "gm: player dead~n"}),
    gen_server:cast(i_server, {gm_fail}).
