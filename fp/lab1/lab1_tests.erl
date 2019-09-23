-module(lab1_tests).

-include_lib("eunit/include/eunit.hrl").

empty_list_test() ->
    ?assertEqual(0, lab1:expr([])).

one_element_list_test() ->
    ?assertEqual(1, lab1:expr([1])).

plus_simple_expression_test() ->
    ?assertEqual(3, lab1:expr(["+", 1, 2])).

minus_simple_expression_test() ->
    ?assertEqual(-1, lab1:expr(["-", 1, 2])).

mul_simple_expression_test() ->
    ?assertEqual(2, lab1:expr(["*", 1, 2])).

div_simple_expression_test() ->
    ?assertEqual(0.5, lab1:expr(["/", 1, 2])).

level_3_expression_tree_1_test() ->
    ?assertEqual(6, lab1:expr(["*", "+", "-", 1, 2, 7, 5])).

level_3_expression_tree_2_test() ->
    ?assertEqual(-7, lab1:expr(["*", 7, "-", 1, 2])).

level_3_expression_tree_3_test() ->
    ?assertEqual(21, lab1:expr(["*", "+", 7, 1, 2])).

plus_is_oper_test() ->
    ?assertEqual(true, lab1:is_oper("+")).

minus_is_oper_test() ->
    ?assertEqual(true, lab1:is_oper("-")).

mul_is_oper_test() ->
    ?assertEqual(true, lab1:is_oper("*")).

div_is_oper_test() ->
    ?assertEqual(true, lab1:is_oper("/")).

num_is_oper_test() ->
    ?assertEqual(false, lab1:is_oper(1)).

first_item_of_test() ->
    ?assertEqual(2, lab1:item_of(1, [2, 3, 4])).

middle_item_of_test() ->
    ?assertEqual(3, lab1:item_of(2, [2, 3, 4])).

last_item_of_test() ->
    ?assertEqual(4, lab1:item_of(3, [2, 3, 4])).

not_found_item_of_test() ->
    ?assertEqual(not_found, lab1:item_of(5, [1, 2, 3])).

