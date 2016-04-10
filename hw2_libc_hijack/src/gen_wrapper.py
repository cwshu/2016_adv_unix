#!/usr/bin/env python3

# func.name: libc function name
# PARAMETERS: function parameter type and name
    # PARAMETERS_NAME
    # [X] PARAMETERS_TYPE_PRINTF

# func.ret_type: return type
    # [X] func.ret_type_PRINTF

wrapper_template='''static {ret_type} (*real_{name})({parameters});

{ret_type} {name}({parameters}){{
    if(!log_file){{
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        log_file = real_fopen(LOG_FILE_NAME, "w");
    }}

    {ret_type} ret;

    real_{name} = dlsym(RTLD_NEXT, "{name}");
    ret = real_{name}({parameters_name});

    fprintf(stderr, "{name}[{parameters_type_printf}] = {ret_type_printf}\\n", {parameters_name}, ret);

    return ret;
}}'''

libc_functions = [
    {'name': 'open', 'parameters': 'const char *path, int oflag, ...', 'ret_type': 'int', 'parameters_name': 'path, oflag'}, 
    {'name': 'fopen', 'parameters': 'const char *path, const char *mode', 'ret_type': 'FILE*', 'parameters_name': 'path, mode'}, 
    {'name': 'read', 'parameters': 'int fildes, void *buf, size_t nbyte', 'ret_type': 'ssize_t', 'parameters_name': 'fildes, buf, nbyte'}, 
    {'name': 'write', 'parameters': 'int fildes, const void *buf, size_t nbyte', 'ret_type': 'ssize_t', 'parameters_name': 'fildes, buf, nbyte'}, 
    {'name': 'fwrite', 'parameters': 'const void *ptr, size_t size, size_t nmemb, FILE *stream', 'ret_type': 'size_t', 'parameters_name': 'ptr, size, nmemb, stream'}, 
    {'name': 'close', 'parameters': 'int fildes', 'ret_type': 'int', 'parameters_name': 'fildes'}, 
    {'name': 'fclose', 'parameters': 'FILE* stream', 'ret_type': 'int', 'parameters_name': 'stream'}, 
]

output_functions = []
for func in libc_functions:
    output_functions.append(
        wrapper_template.format(**func, ret_type_printf="RET_TYPE_PRINTF", parameters_type_printf="PARAMETERS_TYPE_PRINTF")
    )

print('\n\n'.join(output_functions))
