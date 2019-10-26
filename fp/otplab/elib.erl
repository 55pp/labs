-module(elib).

-export([attack/1, damage/1]).

attack({Health, Key}) ->
    gen_event:notify(event_logger, {msg, "enemy: start attack~n"}),
    gen_server:cast(p_server, {damage, Health - 10, Key, 30}),
    ok.

damage({PHealth, PKey, EHealth}) ->
    gen_event:notify(event_logger, {msg, "enemt: damage~n"}),
    gen_server:cast(p_server, {damage, PHealth - 10, PKey, EHealth}),
    ok.
