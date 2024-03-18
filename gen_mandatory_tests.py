"""
This script generate tests cases for C printf function.
Result is test cases each in new line in format: `run_test_case((*f)(<format>, <arguments>));`
where <format> is a string like `"%d %d"`, and <arguments> is respective arguments like `42, 73`.
Values for pointer conversion has to be cast to `uintptr_t` type.
"""
from random import randint, sample

mandatory_conf = {
    "n_per_type": 100,
    2: 15,
    3: 15,
    5: 10,
    10: 10,
}

SUPPORTED_CONVERSIONS = ["c", "s", "p", "d", "i", "u", "x", "X", "%"]
CONVERSION_VALUE_LIMITS = {
    "d": (-(2**31), 2**31 - 1),
    "i": (-(2**31), 2**31 - 1),
    "u": (0, 2**32 - 1),
    "x": (0, 2**32 - 1),
    "X": (0, 2**32 - 1),
    "p": (0, 2**64 - 1),
    "c": (-(2**31), 2**31 - 1),
    # for string some random string and NULL
}


def gen_tests(conf: dict):
    for k, v in conf.items():
        if k == "n_per_type":
            gen_each_type_tests(v)
        else:
            gen_multiconv_tests(k, v)


# make sure all test cases are unique
def gen_each_type_tests(n: int):
    for conv in SUPPORTED_CONVERSIONS:
        if conv == "%":
            print(f'run_test_case((*f)("%%"));')
            continue
        conv_tests = set()
        if conv in CONVERSION_VALUE_LIMITS:
            p_cast = "(uintptr_t)" if conv == "p" else ""
            conv_tests.add(f'run_test_case((*f)("%{conv}", {p_cast}{CONVERSION_VALUE_LIMITS[conv][0]}));')
            conv_tests.add(f'run_test_case((*f)("%{conv}", {p_cast}{CONVERSION_VALUE_LIMITS[conv][1]}));')
            while len(conv_tests) < n:
                conv_tests.add(gen_single_conv_test_case(conv))
        elif conv == "s":
            conv_tests.add(f'run_test_case((*f)("%{conv}", NULL));')
            while len(conv_tests) < n:
                conv_tests.add(gen_text_test_case())
        else:
            raise ValueError(f"Unsupported conversion: {conv}")
        for test in conv_tests:
            print(test)


def gen_single_conv_test_case(conv: str) -> str:
    format, arg = gen_format_arg(conv)
    return f'run_test_case((*f)("{format}", {arg}));'


def gen_format_arg(conv: str) -> tuple:
    limits = CONVERSION_VALUE_LIMITS[conv]
    cast = "(uintptr_t)" if conv == "p" else ""
    value = randint(limits[0], limits[1])
    return f"%{conv}", f"{cast}{value}"


def gen_text_test_case() -> str:
    return f'run_test_case((*f)("%s", "{get_rand_text()}"));'


def get_rand_text() -> str:
    text_length = randint(5, 100)
    # protect escape characters like \, ", etc.
    t = "".join(chr(randint(32, 126)) for _ in range(text_length))
    t = t.replace("\\", "\\\\").replace('"', '\\"')
    return t


def gen_multiconv_tests(n_convs: int, n: int):
    for _ in range(n):
        convs = []
        args = []
        for _ in range(n_convs):
            conv = sample(SUPPORTED_CONVERSIONS, 1)[0]
            if conv in CONVERSION_VALUE_LIMITS:
                format, arg = gen_format_arg(conv)
                convs.append(format)
                args.append(arg)
            elif conv == "s":
                convs.append("%s")
                args.append(f'"{get_rand_text()}"')
            elif conv == "%":
                convs.append("%%")
        print(f'run_test_case((*f)("{" ".join(convs)}", {", ".join(args)}));')


if __name__ == "__main__":
    gen_tests(mandatory_conf)
