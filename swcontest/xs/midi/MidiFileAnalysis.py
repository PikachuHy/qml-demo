import os

MFile = "MFile"
MTrk = "MTrk"
TrkEnd = "TrkEnd"
Tempo = "Tempo"
KeySig = "KeySig"
major = "major"
Meta = "Meta"
SeqName = "SeqName"
TimeSig = "TimeSig"
Par = "Par"
On = "On"
Off = "Off"
PrCh = "PrCh"
TrkName = "TrkName"


# return the value of n ,when receiving an input like str "n=x"
def find_value(temp_x):
    # print temp_x
    temp_x = temp_x.split('=')
    # print temp_x[0] + temp_x[1]
    return int(temp_x[1])


# translate pitch position into time duration in 1/600 second according to the tempo and distinguishability.
# using 1/600 second will be convenience for matching fps
# def exchange_time(position, dis, tempo):
#     speed = 60000000 / tempo
#     time = 1.0 * position / dis / speed * 36000
#     return int(round(time))
def exchange_time(position, dis, tempo_point, tempo_list):
    speed = 1.0 * 60000000 / tempo_list[tempo_point][1]
    pre_position = tempo_list[tempo_point][0]
    pre_time = tempo_list[tempo_point - 1][2]
    position = position - pre_position
    time = 1.0 * position / dis / speed * 36000
    return time + pre_time


# find the position of the pitch according to the steps and fps.Set default speed as 60,dis as 480.
def exchange_position(step_num, fps):
    time = step_num * 600 / fps
    position = 1.0 * time / 36000 * 480 * 60
    return position


# divide vol into ten levels
def divide_vol(vol):
    divided_vol = round(vol / 10.0)
    if divided_vol >= 10.0:
        return 9.0
    return divided_vol


# def search_tempo(position, tempo_list):
#     for x in tempo_list:
#         if x[0] > position:
#             return temp[1]
#         temp = x
#     return tempo_list[len(tempo_list) - 1][1]


def search_tempo(position, tempo_list):
    for x in range(len(tempo_list)):
        if tempo_list[x][0] > position:
            return x - 1
    return len(tempo_list) - 1


def channel_merge(l_list):
    l_list = sorted(l_list, key=lambda unit: unit[1])
    return l_list


# analysis the midi txt,and return a list of pitch,start_time,end_time,start_vol,end_vol
def analysis(midi_txt_name):
    # Get Current Directory
    cur_dir = os.path.split(os.path.realpath(__file__))[0]
    midi_file = open(os.path.join(cur_dir, midi_txt_name))
    # lList is used for saving when the pitch is on and duration and vol start and vol end
    # l_list = [[0 for i in range(5)] for j in range(10000)]
    l_list = []
    l_point = 0
    # nList is used for saving which pitch has not end;
    n_list = [0] * 10000
    tempo_list = [[0, 0, 0]]
    for line in midi_file:
        temp = line.split()
        if temp[0] == MFile:
            dis = int(temp[3])

        elif temp[0] == MTrk:
            continue

        elif temp[0] == TrkEnd:
            continue

        elif temp[0] == "0":
            if temp[1] == Tempo:
                # do tempo
                # tempo = int(temp[2])
                tempo_list.append([0, int(temp[2]), 0])  # start_position tempo start_time
            elif temp[1] == KeySig:
                # do KeySig
                continue
            elif temp[1] == Meta:
                if temp[2] == SeqName:
                    # do SeqName
                    continue
                elif temp[2] == TrkEnd:
                    # do TrkEnd
                    continue
            elif temp[1] == Par:
                continue
            elif temp[1] == PrCh:
                continue
            elif temp[1] == On:
                unit = [0 for i in range(5)]
                n = find_value(temp[3])
                unit[0] = n
                # tempo = search_tempo(int(temp[0]), tempo_list)
                # unit[1] = exchange_time(int(temp[0]), dis, tempo)
                tempo_point = search_tempo(int(temp[0]), tempo_list)
                unit[1] = exchange_time(int(temp[0]), dis, tempo_point, tempo_list)
                # print(unit[1])

                n_list[n] = int(temp[0])
                v = find_value(temp[4])
                unit[3] = divide_vol(v)
                l_list.append(unit)
                l_point += 1

        else:
            if temp[1] == Meta:
                if temp[2] == TrkEnd:
                    continue
                else:
                    continue
            elif temp[1] == On:
                unit = [0 for i in range(5)]
                n = find_value(temp[3])
                unit[0] = n
                tempo_point = search_tempo(int(temp[0]), tempo_list)
                unit[1] = exchange_time(int(temp[0]), dis, tempo_point, tempo_list)
                # if int(temp[0])==249600:
                # print("AAAAAAAA"+str(unit[1]))
                # print(unit[1])
                n_list[n] = l_point
                v = find_value(temp[4])
                unit[3] = divide_vol(v)
                l_list.append(unit)
                l_point += 1
            elif temp[1] == Off:
                n = find_value(temp[3])
                end_time = int(temp[0])
                v = find_value(temp[4])
                li = n_list[n]

                # tempo = search_tempo(int(temp[0]), tempo_list)
                # l_list[li][2] = exchange_time(int(end_time), dis, tempo)
                tempo_point = search_tempo(int(temp[0]), tempo_list)
                l_list[li][2] = exchange_time(int(end_time), dis, tempo_point, tempo_list)

                l_list[li][4] = divide_vol(v)
            elif temp[1] == Tempo:
                # tempo = int(temp[2])
                tempo_list.append([int(temp[0]), int(temp[2]), 0])
                endtime = exchange_time(int(temp[0]), dis, len(tempo_list) - 2, tempo_list)
                tempo_list[len(tempo_list) - 2][2] = endtime

            elif temp[1] == Par:
                continue
            elif temp[1] == TimeSig:
                continue
            elif temp[1] == KeySig:
                continue
            else:
                print("row[2] error" + temp[1] + midi_txt_name)
    midi_file.close()
    return l_list


def test_analysis():
    l_list = analysis("panama.txt")
    file_out = open("panama-result.txt", 'wt')
    l_list = channel_merge(l_list)
    for record in l_list:
        for item in record:
            file_out.write(str(item) + " ")
        file_out.write("\n")
    file_out.close()


# if __name__ == '__main__':
#     test_analysis()
#     exit(0)

def generate_head(music_name, iid):
    mf = open(music_name + ".txt", "w")
    mf.write(MFile + " " + "1 3" + " " + "480" + "\n")
    mf.write(MTrk + "\n")
    mf.write("0" + " " + Tempo + " " + "1000000" + "\n")
    mf.write("0" + " " + KeySig + " " + "0 major" + "\n")
    mf.write("0" + " " + Meta + " " + SeqName + " \"" + music_name + "\"" + "\n")
    mf.write("0" + " " + TimeSig + " " + "4/4" + " " + "24 8" + "\n")
    mf.write("0" + " " + Meta + " " + TrkEnd + "\n")
    mf.write(TrkEnd + "\n")
    mf.write(MTrk + "\n")
    mf.write("0 PrCh ch=1 p=" + str(iid) + "\n")
    mf.close()


def generate(music_name, position, is_on, n, v):
    mf = open(music_name + ".txt", "a")
    if is_on:
        mf.write(str(int(round(position))) + " " + On + " " + "ch=1" + " " + "n=" + str(n) + " " + "v=" + str(v) + "\n")
    else:
        mf.write(
            str(int(round(position))) + " " + Off + " " + "ch=1" + " " + "n=" + str(n) + " " + "v=" + str(v) + "\n")


def generate_ending(music_name):
    mf = open(music_name + ".txt", "a")
    mf.write(TrkEnd + "\n")
    mf.write(MTrk + "\n")
    mf.write("0" + " " + Meta + " " + TrkName + " " + "\"\\xffffffb1\\xffffffea\\xffffffbc\\xffffffc7\"" + "\n")
    mf.write("0" + " " + Meta + " " + TrkEnd + "\n")
    mf.write(TrkEnd + "\n")
    mf.close()
