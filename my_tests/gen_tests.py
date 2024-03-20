"""
This script generate tests cases for C printf function.
Result is test cases each in new line in format: `print_length((*f)(<format>, <arguments>));`
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

ALT_FORMS = [None, "#"]
SIGNS = [None, "+", " "]
ZERO_FILL_STARTS = ["0"]
STANDARD_FILL_STARTS = [None, "-"]
ALL_FILL_STARTS = STANDARD_FILL_STARTS + ZERO_FILL_STARTS
PRECISION = [None, "."]
POSSIBLE_CONVERSION_FLAGS = {
    "d": [SIGNS, ALL_FILL_STARTS, PRECISION],
    "i": [SIGNS, ALL_FILL_STARTS, PRECISION],
    "u": [ALL_FILL_STARTS, PRECISION],
    "x": [ALT_FORMS, ALL_FILL_STARTS, PRECISION],
    "X": [ALT_FORMS, ALL_FILL_STARTS, PRECISION],
    "c": [STANDARD_FILL_STARTS],
    "s": [STANDARD_FILL_STARTS, PRECISION],
    "p": [STANDARD_FILL_STARTS],
    "%": [],
}


def gen_tests(conf: dict, flags: dict = None):
    for k, v in conf.items():
        if k == "n_per_type":
            gen_each_type_tests(v, flags)
        else:
            gen_multiconv_tests(k, v, flags)


# make sure all test cases are unique
def gen_each_type_tests(n: int, flags: dict = None):
    for conv in SUPPORTED_CONVERSIONS:
        if conv == "%":
            print(f'print_length((*f)("%%"));')
            continue
        conv_tests = set()
        if conv in CONVERSION_VALUE_LIMITS:
            p_cast = "(uintptr_t)" if conv == "p" else ""
            conv_tests.add(
                f'print_length((*f)("%{gen_format_flags(conv, flags)}{conv}", {p_cast}{CONVERSION_VALUE_LIMITS[conv][0]}));'
            )
            conv_tests.add(
                f'print_length((*f)("%{gen_format_flags(conv, flags)}{conv}", {p_cast}{CONVERSION_VALUE_LIMITS[conv][1]}));'
            )
            if conv == "p":
                conv_tests.add(f'print_length((*f)("%{gen_format_flags(conv, flags)}{conv}", NULL));')
            while len(conv_tests) < n:
                conv_tests.add(gen_single_conv_test_case(conv, flags))
        elif conv == "s":
            while len(conv_tests) < n:
                conv_tests.add(gen_text_test_case(flags))
        else:
            raise ValueError(f"Unsupported conversion: {conv}")
        for test in conv_tests:
            print(test)


def gen_single_conv_test_case(conv: str, flags: dict = None) -> str:
    format, arg = gen_format_arg(conv, flags)
    return f'print_length((*f)("{format}", {arg}));'


def gen_format_arg(conv: str, flags: dict = None) -> tuple:
    _flags = gen_format_flags(conv, flags)
    cast = "(uintptr_t)" if conv == "p" else ""
    limits = CONVERSION_VALUE_LIMITS[conv]
    if _flags:
        limits = (-2 + (limits[0] < 0)) * (abs(limits[0]) % 100), limits[1] % 100
    value = randint(limits[0], limits[1])
    return f"%{_flags}{conv}", f"{cast}{value}"


def gen_format_flags(conv: str, flags: dict = None) -> str:
    _flags = ""
    if flags and conv in flags:
        for flag_type in flags[conv]:
            flag = sample(flag_type, 1)[0]
            if flag:
                if flag == "." and "0" in _flags:
                    continue
                _flags += flag
            if "-" in flag_type:
                _flags += str(randint(10, 20))
            if flag == ".":
                _flags += str(randint(0, 15))
    return _flags


def gen_text_test_case(flags: dict = None) -> str:
    _flags = gen_format_flags("s", flags)
    return f'print_length((*f)("%{_flags}s", "{get_rand_text()}"));'


def get_rand_text() -> str:
    text_length = randint(5, 100)
    # protect escape characters like \, ", etc.
    t = "".join(chr(randint(32, 126)) for _ in range(text_length))
    t = t.replace("\\", "\\\\").replace('"', '\\"')
    return t


def gen_multiconv_tests(n_convs: int, n: int, flags: dict = None):
    for _ in range(n):
        convs = []
        args = []
        for _ in range(n_convs):
            conv = sample(SUPPORTED_CONVERSIONS, 1)[0]
            if conv in CONVERSION_VALUE_LIMITS:
                format, arg = gen_format_arg(conv, flags)
                convs.append(format)
                args.append(arg)
            elif conv == "s":
                convs.append(f"%{gen_format_flags(conv, flags)}s")
                args.append(f'"{get_rand_text()}"')
            elif conv == "%":
                convs.append("%%")
        print(f'print_length((*f)("{" ".join(convs)}", {", ".join(args)}));')


if __name__ == "__main__":
    # gen_tests(mandatory_conf)
    gen_tests(mandatory_conf, POSSIBLE_CONVERSION_FLAGS)
