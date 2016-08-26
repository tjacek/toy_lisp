Env = dict          

def standard_env():
    env = Env()
    env.update({'car':     lambda x: x[0],
                'cdr':     lambda x: x[1:], 
                'cons':    lambda x,y: [x] + y})
    return env
    
