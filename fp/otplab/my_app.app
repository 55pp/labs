{application, my_app,
[{description, "some kind of lab"},
{vsn, "1.0"},
{modules, [my_app, my_svisor,
 i_server, ilib]}, 
 {registered, [ i_server, my_svisor]},
 {applications, [kernel, stdlib]},
 {mod, {my_app,[]}},
 {start_phases, []}]}.