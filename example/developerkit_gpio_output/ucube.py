src     = Split('''
        gpio_demo.c
''')

component = aos_component('gpio_demo', src)
component.add_comp_deps('kernel/yloop', 'tools/cli')
component.add_global_macros('AOS_NO_WIFI')
