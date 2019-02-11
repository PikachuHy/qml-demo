import datetime
import logging


def timer(label=None):
    def decorator(func):
        def wrapper(*args, **kwargs):
            begin = datetime.datetime.now()
            logging.info('{} is running'.format(func.__name__))
            ret = func(*args, **kwargs)
            end = datetime.datetime.now()
            if label is None:
                title = func.__name__
            else:
                title = label
            print('{} cost time: {}'.format(title, end - begin))
            return ret

        return wrapper

    return decorator
