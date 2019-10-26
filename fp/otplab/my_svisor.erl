%%%-------------------------------------------------------------------
%%% @author tester <tester@testerPC>
%%% @copyright (C) 2019, tester
%%% @doc
%%%
%%% @end
%%% Created : 23 Oct 2019 by tester <tester@testerPC>
%%%-------------------------------------------------------------------
-module(my_svisor).

-behaviour(supervisor).

%% API
-export([start_link/0]).

%% Supervisor callbacks
-export([init/1]).

-define(SERVER, ?MODULE).

%%%===================================================================
%%% API functions
%%%===================================================================

%%--------------------------------------------------------------------
%% @doc
%% Starts the supervisor
%%
%% @spec start_link() -> {ok, Pid} | ignore | {error, Error}
%% @end
%%--------------------------------------------------------------------
start_link() ->
    supervisor:start_link({local, ?SERVER}, ?MODULE, []).

%%%===================================================================
%%% Supervisor callbacks
%%%===================================================================

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Whenever a supervisor is started using supervisor:start_link/[2,3],
%% this function is called by the new process to find out about
%% restart strategy, maximum restart intensity, and child
%% specifications.
%%
%% @spec init(Args) -> {ok, {SupFlags, [ChildSpec]}} |
%%                     ignore |
%%                     {error, Reason}
%% @end
%%--------------------------------------------------------------------
init([]) ->

    SupFlags = #{strategy => one_for_one,
		 intensity => 1,
		 period => 5},

    AChild = #{id => iserver,
	       start => {i_server, start_link, []},
	       restart => permanent,
	       shutdown => 5000,
	       type => worker,
	       modules => [i_server]},


    BChild = #{id => logger,
	       start => {event_logger, start_link, []},
	       restart => permanent,
	       shutdown => 5000,
	       type => worker,
	       modules => [event_logger]},

    CChild = #{id => gmserver,
	       start => {gm_server, start_link, []},
	       restart => permanent,
	       shutdown => 5000,
	       type => worker,
	       modules => [gm_server]},

    DChild = #{id => rserver,
	       start => {r_server, start_link, []},
	       restart => permanent,
	       shutdown => 5000,
	       type => worker,
	       modules => [r_server]},

    EChild = #{id => eserver,
	       start => {e_server, start_link, []},
	       restart => permanent,
	       shutdown => 5000,
	       type => worker,
	       modules => [e_server]},

    FChild = #{id => pserver,
	       start => {p_server, start_link, []},
	       restart => permanent,
	       shutdown => 5000,
	       type => worker,
	       modules => [p_server]},


    {ok, {SupFlags, [AChild, BChild, CChild, DChild, EChild, FChild]}}.

%%%===================================================================
%%% Internal functions
%%%===================================================================
