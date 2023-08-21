# Translating
To create a new translation of Viral, open POEdit and select `Create new translation from POT file`, and in the file selection dialog select the `com.github.ranguli.Viral.pot` in the `po` directory. Once you have finished translation open a pull request from the forked repository to the source repository on the `develop` branch.
___
Whenever you add or update a translation, please also update the source translation from source code changes with this command in the project's root directory:
```sh
xgettext --from-code=UTF-8  --add-comments --keyword=_ --keyword=C_:1c,2 --output=po/com.github.ranguli.Viral.pot -f po/POTFILES
```
Thank you for translating this project.
