vscode配置

```
"cpp": "rm -rf $dir/../build && mkdir $dir/../build && cd $dir && g++ $fileName -I $dir/../ -o $dir/../build/$fileNameWithoutExt -l gtest -l gtest_main -l pthread && $dir/../build/$fileNameWithoutExt"
```
