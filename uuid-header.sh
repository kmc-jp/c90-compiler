#!/bin/bash

which uuidgen >/dev/null 2>&1 && {
    uuidcmd='uuidgen -r'
} || {
    uuidcmd='uuid -v4'
}

for filename in "$@"
do
    uuid=$(${uuidcmd} | tr '[a-f-]' '[A-F_]')
    macro="INCLUDE_GUARD_UUID_${uuid}"
    ifndef="#ifndef ${macro}"
    define="#define ${macro}"
    endif="#endif  /* ${macro} */"
    cat <<EOF >"${filename}"
${ifndef}
${define}

${endif}
EOF
done
