import os

data = []  # the database of pitch combination
live_pitch = []  # the pitch which is on
pre_pitch = []
now_pitch = []


# p = 0  # the pointer of l_list


def add_live_pitch(p, now, l_list):
    for x in range(p, len(l_list)):
        if l_list[x][1] <= now:
            live_pitch.append([l_list[x][0], l_list[x][2]])
            p += 1
        else:
            break
    return p


def remove_dead_pitch(now):
    for x in live_pitch:
        if x[1] <= now:
            live_pitch.remove(x)
            remove_dead_pitch(now)
            break


def pitch_merge():
    unit = []
    for x in live_pitch:
        flag = False
        for y in unit:
            if x[0] == y:
                flag = True
        if not flag:
            unit.append(x[0])
    unit.sort()
    return unit


# search if the pitch combination already exists in the database
def match_pitch_combination(pc):
    for x in range(0, len(data)):
        if len(data[x]) == len(pc):
            flag = True
            for y in range(0, len(pc)):
                if data[x][y] != pc[y]:
                    flag = False
                    break
            if flag:
                return x
        else:
            continue
    return -1


# main entry
def make_data(fps, l_list, frame):
    point_start = 0
    now = 0
    step = 600 / fps
    sign_list = []  # the list of id appeared
    for i in range(0, len(live_pitch)):  # init live_pitch
        live_pitch.pop()
    for i in range(frame):
        point_start = add_live_pitch(point_start, now, l_list)
        remove_dead_pitch(now)
        pc = pitch_merge()
        pid = match_pitch_combination(pc)
        if pid == -1:
            data.append(pc)
            pid = len(data) - 1
        sign_list.append(pid)
        now += step
    return sign_list


# find out if the pitch is in list
def find_pitch(pitch_list, pitch):
    for x in range(len(pitch_list)):
        if pitch_list[x] == pitch:
            return x
    return -1


# find out which pitch need to be on and which need to be off
def find_on_and_off(label):
    on = []
    off = []

    for i in range(len(now_pitch)):
        now_pitch.pop()
    for x in data[label]:
        now_pitch.append(x)
        if find_pitch(pre_pitch, x) == -1:
            on.append(x)
    for y in pre_pitch:
        if find_pitch(now_pitch, y) == -1:
            off.append(y)
    for x in range(len(pre_pitch)):
        pre_pitch.pop()
    for x in now_pitch:
        pre_pitch.append(x)
    return [on, off]


# clear the pre_pitch when the generate is over
def clear_pre():
    for i in range(len(pre_pitch)):
        pre_pitch.pop()


def export_database(txt_name):
    fi = open(txt_name, "w")
    for x in data:
        for y in x:
            fi.write(str(y) + " ")
        fi.write("\n")
    fi.close()


def load_database(txt_name):
    for x in range(0, len(data)):
        data.pop()
    if not os.path.exists(txt_name):
        fi = open(txt_name, 'w')
        fi.close()
    else:
        fi = open(txt_name)
        for line in fi:
            temp = line.split()
            unit = []
            for x in temp:
                unit.append(int(x))
            data.append(unit)
        fi.close()
