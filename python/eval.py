def eval(x, env=global_env):
    if isinstance(x, str):      
        return env[x]
    elif not isinstance(x, list):  
        return x                
    elif x[0] == 'if':         
        (_, test, conseq, alt) = x
        exp = (conseq if eval(test, env) else alt)
        return eval(exp, env)
    elif x[0] == 'define':        
        (_, var, exp) = x
        env[var] = eval(exp, env)
    else:
        proc = eval(x[0], env)
        args = [eval(arg, env) for arg in x[1:]]
        return proc(*args)