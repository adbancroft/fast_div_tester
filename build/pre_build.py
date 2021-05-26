import os

Import("env")

def before_build():
    op = 'DIV'
    genfile = os.path.join(env['PROJECT_SRC_DIR'], 'test.g.hpp')
    print(f'Generating {genfile}')
    with open(genfile, 'w') as f:
        for index in range(768+3, 1024+3):
            print(f'Serial.print(F("{op}_{index} "));', file=f)
            print(f'testCheckSum(TEST_NATIVE_{op}({index}));', file=f)
            print('Serial.print(" ");', file=f)
            print(f'testCheckSum(TEST_FAST_{op}({index}));', file=f) 
            print('Serial.println("");', file=f)

before_build()