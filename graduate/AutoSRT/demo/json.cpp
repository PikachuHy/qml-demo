//
// Created by PikachuHy on 2019/12/17.
//
#include <string>
#include <vector>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using std::string;
using std::vector;

string json = R"(
{
    "Sentences":[
        {
            "EndTime":10300,
            "SilenceDuration":0,
            "BeginTime":2420,
            "Text":"最后还有几个特殊的符号在文档里面，游戏第一个是这个类似于灯泡的，在圈圈里面有个擦擦。",
            "ChannelId":0,
            "SpeechRate":296,
            "EmotionValue":6.9
        },
        {
            "EndTime":12670,
            "SilenceDuration":0,
            "BeginTime":10490,
            "Text":"然后这个的时候就是。",
            "ChannelId":0,
            "SpeechRate":247,
            "EmotionValue":6.3
        },
        {
            "EndTime":17650,
            "SilenceDuration":1,
            "BeginTime":14340,
            "Text":"3ix是这样子。",
            "ChannelId":0,
            "SpeechRate":108,
            "EmotionValue":6.5
        },
        {
            "EndTime":21340,
            "SilenceDuration":0,
            "BeginTime":17900,
            "Text":"哦。我这个清单里面一个一个账号就是。",
            "ChannelId":0,
            "SpeechRate":279,
            "EmotionValue":6.5
        },
        {
            "EndTime":23570,
            "SilenceDuration":0,
            "BeginTime":21520,
            "Text":"方面开始，然后数学奖。",
            "ChannelId":0,
            "SpeechRate":263,
            "EmotionValue":6.4
        },
        {
            "EndTime":26550,
            "SilenceDuration":0,
            "BeginTime":24210,
            "Text":"就会这个方框就是。",
            "ChannelId":0,
            "SpeechRate":205,
            "EmotionValue":6.7
        },
        {
            "EndTime":32360,
            "SilenceDuration":1,
            "BeginTime":27910,
            "Text":"下个田字就是。",
            "ChannelId":0,
            "SpeechRate":80,
            "EmotionValue":6.4
        },
        {
            "EndTime":37420,
            "SilenceDuration":1,
            "BeginTime":33370,
            "Text":"看。",
            "ChannelId":0,
            "SpeechRate":14,
            "EmotionValue":6.3
        },
        {
            "EndTime":46280,
            "SilenceDuration":0,
            "BeginTime":37790,
            "Text":"还有一个常用的就是不等号不等号的话，true很好，还要这个希望就是不同。",
            "ChannelId":0,
            "SpeechRate":212,
            "EmotionValue":6.5
        },
        {
            "EndTime":51420,
            "SilenceDuration":1,
            "BeginTime":47650,
            "Text":"那你说个小雨这样子就是。",
            "ChannelId":0,
            "SpeechRate":175,
            "EmotionValue":6.6
        },
        {
            "EndTime":52710,
            "SilenceDuration":0,
            "BeginTime":52100,
            "Text":"行。",
            "ChannelId":0,
            "SpeechRate":98,
            "EmotionValue":6.8
        },
        {
            "EndTime":54990,
            "SilenceDuration":0,
            "BeginTime":53380,
            "Text":"有个附近的好。",
            "ChannelId":0,
            "SpeechRate":223,
            "EmotionValue":6
        },
        {
            "EndTime":59290,
            "SilenceDuration":0,
            "BeginTime":55660,
            "Text":"嗯，还有一个就是在电脑上面输入这个。",
            "ChannelId":0,
            "SpeechRate":264,
            "EmotionValue":6.8
        },
        {
            "EndTime":61460,
            "SilenceDuration":1,
            "BeginTime":60360,
            "Text":"有这个字母。",
            "ChannelId":0,
            "SpeechRate":272,
            "EmotionValue":6.6
        },
        {
            "EndTime":63660,
            "SilenceDuration":0,
            "BeginTime":61740,
            "Text":"在我电脑上面。",
            "ChannelId":0,
            "SpeechRate":187,
            "EmotionValue":6.6
        },
        {
            "EndTime":67700,
            "SilenceDuration":1,
            "BeginTime":66270,
            "Text":"我说这个。",
            "ChannelId":0,
            "SpeechRate":167,
            "EmotionValue":6.6
        },
        {
            "EndTime":70400,
            "SilenceDuration":0,
            "BeginTime":68140,
            "Text":"他是直接在。",
            "ChannelId":0,
            "SpeechRate":132,
            "EmotionValue":6.7
        },
        {
            "EndTime":73600,
            "SilenceDuration":0,
            "BeginTime":70980,
            "Text":"首先过上面的我也不知道为什么。",
            "ChannelId":0,
            "SpeechRate":320,
            "EmotionValue":6.6
        },
        {
            "EndTime":79390,
            "SilenceDuration":2,
            "BeginTime":75950,
            "Text":"我这里面说强制是那个。",
            "ChannelId":0,
            "SpeechRate":174,
            "EmotionValue":6.9
        }
    ]
}
)";
struct Sentence {
    long beginTime;
    long endTime;
    QString text;
    static Sentence fromJSON(QJsonObject o) {
        Sentence ret;
        ret.beginTime = o["BeginTime"].toInt();
        ret.endTime = o["EndTime"].toInt();
        ret.text = o["Text"].toString();
        return ret;
    }
};
int main() {
    auto resBody = QByteArray::fromStdString(json);
    QJsonDocument jsonDocument = QJsonDocument::fromJson(resBody);
    QJsonObject jsonObject = jsonDocument.object();
    QJsonArray jsonArray = jsonObject["Sentences"].toArray();
    vector<Sentence> sentences;
    for (int i = 0; i < jsonArray.size(); ++i) {
        auto sentenceObject = jsonArray[i].toObject();
        sentences.emplace_back(Sentence::fromJSON(sentenceObject));
    }
    for(auto it: sentences) {
        std::cout << it.beginTime << " " << " " << it.endTime << " " << it.text.toStdString() << std::endl;
    }
    return 0;
}