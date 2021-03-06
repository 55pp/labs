mtype = {m_start, gm_start, gm_done, gm_die, complited, failed, key, health, die, next, atack, damage, stop};

chan init_manager_ch = [0] of {mtype};
chan manager_init_ch = [0] of {mtype};

chan manager_player_ch = [0] of {mtype};
chan player_manager_ch = [0] of {mtype};

chan player_event_ch = [0] of {mtype};

chan player_enemy_ch = [0] of {mtype};

chan player_roll_ch = [0] of{mtype};
chan roll_enemy_ch = [0] of {mtype};


bit start_game = 0;
bit end_game = 0;

int p_health = 100;
byte p_key = 0;

int enemy_dead = 0;

byte e_health = 30;
byte random_num = -1;

proctype init_p()
{
	mtype msg;
	init_manager_ch ! m_start;
	start_game = 1;
	manager_init_ch ? msg;
	
}

proctype manager_p()
{
	mtype msg;
	init_manager_ch ? msg;
	if
		:: (msg == m_start) ->
		{
			printf("recv\n");
		}
		:: else -> skip;
	fi

	printf("manager: start\n");
	manager_player_ch ! gm_start;

	player_manager_ch ? msg;
	if
		:: (msg == gm_done) ->
		{
			printf("complited\n");
			manager_init_ch ! complited;
		}
		:: (msg == gm_die) ->
		{
			printf("failed\n");
			manager_init_ch ! failed;
		}
		:: else -> skip;
	fi
}

proctype player_p()
{
	mtype msg;

	manager_player_ch ? msg;
	printf("player: get start\n");

	player_roll_ch ! next;

	do
		::
		{
			if
				:: (p_key == 3 || p_health >= 5000 || enemy_dead >= 10) ->
				{
					printf("all keys\n");
					//player_enemy_ch ! die;
					printf("send stop");
					player_event_ch ? msg;
					player_roll_ch ! stop;
					printf("send die\n");
					player_manager_ch ! gm_done;
					end_game = 1;
					break;
				}
				:: (p_health == 0) ->
				{
					player_event_ch ? msg;
					//player_enemy_ch ! die;
					player_roll_ch ! stop;
					printf("player dead\n");
					player_manager_ch ! gm_die;
					end_game = 1;
					break;
				}
				:: else -> skip;
			fi
		
			player_event_ch ? msg;
			printf("player: receive message\n");
			if
				:: (msg == damage) ->
				{
					printf("damage\n");
					p_health = p_health - 10;
					player_enemy_ch ! damage;
				}
				:: (msg == key) ->
				{
					printf("key\n");
					p_key = p_key + 1;
					player_roll_ch ! next;
				}
				:: (msg == health) ->
				{
					printf("health\n");
					p_health = p_health + 50;
					player_roll_ch ! next;
				}
				:: (msg == die) ->
				{
					printf("enemy die\n");
					enemy_dead = enemy_dead + 1;
					player_roll_ch ! next;
				}
				:: else -> skip;
			fi
		}
	od
}

proctype roll_p()
{
	mtype msg;

	do
		::
		{
			player_roll_ch ? msg;
			if
			:: (msg == next) ->
			{
				select(random_num : 1 .. 3);
				if
				:: (random_num == 1)
				{
					printf("roll key\n");
					player_event_ch ! key;
				}
				:: (random_num == 2)
				{
					printf("roll health\n");
					player_event_ch ! health;
				}
				:: (random_num == 3)
				{
					printf("roll enemy\n");
					roll_enemy_ch ! atack;
				}
				:: else -> skip;
				fi
			}
			:: (msg == stop) ->
			{
				printf("roll: end_game\n");
				roll_enemy_ch ! stop;
				break;
			}
			:: else -> skip;
			fi
		}
	od
}

proctype enemy_p()
{
	mtype msg;

	do
	::
	{
		roll_enemy_ch ? msg;
		if
			:: (msg == atack) ->
			{
				printf("enemy: start atack\n");
				e_health = 30;
				do
					::
					{
						if
							:: (e_health == 0)
							{
								player_event_ch ! die;
								break;
							}
							:: else -> skip;
						fi
						printf("enemy: send damage\n")
						player_event_ch ! damage;
						player_enemy_ch ? msg;
						if
							:: (msg == damage)
							{
								e_health = e_health - 10;
							}
							:: (msg == die)
							{
								printf("enemy: p_die");
								break;
							}
							:: else -> skip;
						fi
					}
				od
			}
			:: (msg == stop) ->
			{
				printf("enemy: end_game\n");
				break;
			}
			:: else -> skip;
		fi
	}
		
	od
}

active proctype main()
{
	run init_p();
	run manager_p();
	run player_p();
	run roll_p();
	run enemy_p();
}

ltl check_me {[] (start_game -> <> end_game)}