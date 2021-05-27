import os

Import("env")

def before_build():
    gen_range = range(0+3, 512+3)
    op = 'DIV'

    genfile = os.path.join(env['PROJECT_SRC_DIR'], 'test_declares.g.hpp')
    print(f'Generating {genfile}')
    with open(genfile, 'w') as f:
        for index in gen_range:
            print(f'TEST_NATIVE_DIV({index});', file=f)
            print(f'TEST_FAST_DIV({index});', file=f)

    genfile = os.path.join(env['PROJECT_SRC_DIR'], 'test.g.hpp')
    print(f'Generating {genfile}')
    with open(genfile, 'w') as f:
        for index in gen_range:
            print(f'Serial.print("{op}_{index} ");', file=f)
            print(f'testCheckSum(TEST_FUNC_NAME(Native, {index}));', file=f)
            print('Serial.print(" ");', file=f)
            print(f'testCheckSum(TEST_FUNC_NAME(ShiftMul, {index}));', file=f)
            print('Serial.println("");', file=f)

before_build()