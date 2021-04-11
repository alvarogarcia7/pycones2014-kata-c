git init || true
while [ 1 ]; do
  git add .
  git commit --all --message "Saving contents"
  sleep 30
done

