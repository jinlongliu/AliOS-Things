src     = Split('''
        uart_opt.c
''')

component = aos_component('uart_opt', src)
component.add_comp_deps('kernel/yloop', 'tools/cli')
component.add_global_macros('AOS_NO_WIFI')
