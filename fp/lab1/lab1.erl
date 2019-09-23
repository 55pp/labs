%%%-------------------------------------------------------------------
%%% @author tester <tester@testerPC>
%%% @copyright (C) 2019, tester
%%% @doc The binary is specified as a list, each node stores either an
%%% operation code (+ - * /) or a number. Calculate the value of the
%%% expression specified by the tree.
%%% @end
%%% Created : 23 Sep 2019 by tester <tester@testerPC>
%%%-------------------------------------------------------------------
-module(lab1).
-author('tester@testerPC').
-export([expr/1, is_oper/1, item_of/2]).

%%--------------------------------------------------------------------
%% @doc Main function
%% @spec
%% @end
%%--------------------------------------------------------------------

expr([]) ->
    0;
expr(["+" | T]) ->
    expr(T, ["+"], []);
expr(["-" | T]) ->
    expr(T, ["-"], []);
expr(["*" | T]) ->
    expr(T, ["*"], []);
expr(["/" | T]) ->
    expr(T, ["/"], []);
expr([H | _T]) ->
    H.

%%--------------------------------------------------------------------
%% @doc Checking the element(E) for belonging to operators
%% @spec
%% @end
%%--------------------------------------------------------------------

is_oper(E) ->
    contain(["+", "-", "*", "/"], E).

%%--------------------------------------------------------------------
%% @doc Get element of list(L) on index(I)
%% @spec
%% @end
%%--------------------------------------------------------------------

item_of(I, L) ->
    item_of(I, 1, L).

item_of(_I, _CI, []) ->
    not_found;
item_of(I, I, [H | _T]) ->
    H;
item_of(I, CI, [_H | T]) ->
    item_of(I, CI + 1, T).

%%--------------------------------------------------------------------
%%                     INTERNAL FUNCTIONS
%%--------------------------------------------------------------------

contain([], _E) ->
    false;
contain([E | _T], E) ->
    true;
contain([_H | T], E) ->
    contain(T, E).

expr([], O, N) ->
    calc(O, N, []);
expr(S, O, N) ->
    fill(is_oper(item_of(1, S)), is_oper(item_of(2, S)), S, O, N).

fill(true, true, [H1, H2 | T], O, N) ->
    expr(T, [H2] ++ [H1] ++ O, N);
fill(true, false, [H1, H2 | T], O, N) ->
    expr(T, [H1] ++ O, ["x"] ++ [H2] ++ N);
fill(false, true, [H1, H2 | T], O, N) ->
    expr(T, [H2] ++ O, [H1] ++ ["x"] ++ N);
fill(false, false, [H1, H2 | T], O, N) ->
    expr(T, O, [H1] ++ [H2] ++ N).

calc([], _N, [AH | _AT]) ->
    AH;
calc([OH | OT], [], [AH1, AH2 | AT]) ->
    calc_o(OH, OT, AH2, AH1, [], AT);
calc([OH | OT], ["x", NH2 | NT], [AH | AT]) ->
    calc_o(OH, OT, AH, NH2, NT, AT);
calc([OH | OT], [NH1, "x" | NT], [AH | AT]) ->
    calc_o(OH, OT, NH1, AH, NT, AT);
calc([OH | OT], [NH1, NH2 | NT], A) ->
    calc_o(OH, OT, NH1, NH2, NT, A).

calc_o("+", O, OP1, OP2, N, A) ->
    calc(O, N, [(OP1 + OP2)] ++ A);
calc_o("-", O, OP1, OP2, N, A) ->
    calc(O, N, [(OP1 - OP2)] ++ A);
calc_o("*", O, OP1, OP2, N, A) ->
    calc(O, N, [(OP1 * OP2)] ++ A);
calc_o("/", O, OP1, OP2, N, A) ->
    calc(O, N, [(OP1 / OP2)] ++ A).
