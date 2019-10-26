-module(rlib).

-export([roll/1]).

roll({Health, Key}) ->
    roll(rand:uniform(3), {Health, Key}).

roll(1, {Health, Key}) ->
    gen_event:notify(event_logger, {msg, "roll: key~n"}),
    gen_server:cast(p_server, {roll, Health, Key + 1}),
    ok;
roll(2, {Health, Key}) ->
    gen_event:notify(event_logger, {msg, "roll: health~n"}),
    gen_server:cast(p_server, {roll, Health + 50, Key}),
    ok;
roll(3, {Health, Key}) ->
    gen_event:notify(event_logger, {msg, "roll: enemy~n"}),
    gen_server:cast(e_server, {attack, Health, Key}),
    ok.
