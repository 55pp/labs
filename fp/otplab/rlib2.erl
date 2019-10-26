-module(rlib2).

-export([roll/1]).

roll({Health, Key}) ->
    roll(rand:uniform(4), {Health, Key}).

roll(1, {Health, Key}) ->
    gen_event:notify(event_logger, {msg, "roll: key~n"}),
    gen_server:cast(p_server, {roll, Health, Key + 1});
roll(2, {Health, Key}) ->
    gen_event:notify(event_logger, {msg, "roll: health~n"}),
    gen_server:cast(p_server, {roll, Health + 50, Key});
roll(3, {Health, Key}) ->
    gen_event:notify(event_logger, {msg, "roll: enemy~n"}),
    gen_server:cast(e_server, {attack, Health, Key});
roll(4, {Health, 0}) ->
    gen_event:notify(event_logger, {msg, "roll: oops no more keys~n"}),
    gen_server:cast(p_server, {roll, Health, 0});
roll(4, {Health, Key}) ->
    gen_event:notify(event_logger, {msg, "roll: key lost~n"}),
    gen_server:cast(p_server, {roll, Health, Key - 1}).
