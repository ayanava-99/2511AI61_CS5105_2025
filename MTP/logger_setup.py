import logging
import logging.handlers




def setup_logging(logfile='app.log', errorfile='app_error.txt'):
    logger = logging.getLogger('seat_attendance_logs')
    logger.setLevel(logging.DEBUG)


    fmt = logging.Formatter('%(asctime)s | %(levelname)s | %(name)s | %(message)s')


    fh = logging.FileHandler(logfile, mode='w')
    fh.setLevel(logging.DEBUG)
    fh.setFormatter(fmt)
    logger.addHandler(fh)


    eh = logging.FileHandler(errorfile, mode='w')
    eh.setLevel(logging.ERROR)
    eh.setFormatter(fmt)
    logger.addHandler(eh)


    ch = logging.StreamHandler()
    ch.setLevel(logging.INFO)
    ch.setFormatter(fmt)
    logger.addHandler(ch)


    return logger