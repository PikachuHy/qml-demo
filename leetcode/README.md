vscode配置

```
"cpp": "cd $dir && g++ $fileName -I $dir/../ -o $fileNameWithoutExt -l gtest -l gtest_main -l pthread && $dir$fileNameWithoutExt"
```