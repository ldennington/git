#!/bin/bash

SIGN_DIR=$1
DEVELOPER_ID=$2
ENTITLEMENTS_FILE=$3

if [ -z "$SIGN_DIR" ]; then
    echo "error: missing directory argument"
    exit 1
elif [ -z "$DEVELOPER_ID" ]; then
    echo "error: missing developer id argument"
    exit 1
elif [ -z "$ENTITLEMENTS_FILE" ]; then
    echo "error: missing entitlements file argument"
    exit 1
fi

echo "======== INPUTS ========"
echo "Directory: $SIGN_DIR"
echo "Developer ID: $DEVELOPER_ID"
echo "Entitlements: $ENTITLEMENTS_FILE"
echo "======== END INPUTS ========"

sign() {
    echo "Signing $1"
    codesign -s "$DEVELOPER_ID" "$1" --timestamp --force
}

for ITEM in $(find "$SIGN_DIR" -type f)
do
    sign "$ITEM"
done