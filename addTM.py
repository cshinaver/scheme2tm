from turing_machine import TuringMachine

scheme = TuringMachine(
    {
        # setup string
        ('q0',''):('w0','#','R'),
        ('w0',''):('w1','1','R'),
        ('w1',''):('w+','1','R'),
        ('w+',''):('w2','+','R'),
        ('w2',''):('w3','1','R'),
        ('w3',''):('w4','1','R'),
        ('w4',''):('w5','1','R'),
        ('w5',''):('w=','1','R'),
        ('w=',''):('leftMost','=','L'),

        ('q1','1'):('rightMost','x','R'),
        ('q1','+'):('q1','x','R'),
        ('q1','='):('qa','=','R'),

        ('rightMost','1'):('rightMost','1','R'),
        ('rightMost','+'):('rightMost','+','R'),
        ('rightMost','='):('rightMost','=','R'),
        ('rightMost',''):('leftMost','1','L'),

        ('leftMost','1'):('leftMost','1','L'),
        ('leftMost','+'):('leftMost','+','L'),
        ('leftMost','='):('leftMost','=','L'),
        ('leftMost','x'):('q1','x','R'),
        ('leftMost','#'):('q1','#','R'),
    }
)

scheme.debug('',step_limit=1000)
