#!/bin/bash

# 新文件夹名称
new_folder="actual_files"

# 创建新文件夹
mkdir -p "$new_folder"

# 查找所有符号链接
find . -type l | while read symlink; do
  # 获取符号链接的目标
  target=$(readlink "$symlink")
  
  # 备份原符号链接
  cp "$symlink" "bak-$symlink.bak"
  
  # 复制目标文件内容到新文件夹下，并保持原来的文件结构
  # 例如：如果符号链接是 ./subdir/file -> /path/to/target_file
  # 目标文件在新文件夹中的路径将是 new_folder/subdir/file
  relative_path=$(dirname "$symlink")
  mkdir -p "$new_folder/$relative_path"
  cp "$target" "$new_folder/$symlink"
  
  # 删除符号链接
  rm "$symlink"
done
