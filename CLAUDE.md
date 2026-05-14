# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a personal ESPHome configuration repository containing YAML device configs for various ESP32-based hardware integrated with Home Assistant.

## ESPHome CLI

ESPHome is installed in a local virtual environment. Use it with:

```bash
# Activate venv first
source .venv/bin/activate

# Or prefix commands directly
.venv/bin/esphome <command> <config.yaml>
```

Key commands:
- `esphome compile <config.yaml>` — build firmware only
- `esphome run <config.yaml>` — compile and flash via USB
- `esphome upload <config.yaml>` — OTA upload to device
- `esphome logs <config.yaml>` — stream serial/network logs
- `esphome dashboard .` — web UI for managing all configs

## Repository Structure

Each `.yaml` file is a standalone device configuration:

| File | Device | Board | Key features |
|------|--------|-------|--------------|
| `dotaray.yaml` | ESP32 Matrix Display | NodeMCU-32S | MAX7219 LED matrix, reads text from HA `input_text` |
| `esp_clamp_meter.yaml` | ESP32-S3 CT Monitor | esp32-s3-devkitc-1 | CT clamp current sensor |
| `m5dial.yaml` | M5Dial | ESP32-S3 | GC9A01A round display, LVGL, rotary encoder, media player + pomodoro |
| `round_display.yaml` | Round Display | ESP32-C3 | GC9A01A round display, LVGL, CST816 touch, media player + pomodoro |
| `presence_sensor.yaml` | Presence Sensor | NodeMCU-32S | PIR motion on GPIO13 |
| `shelly_relay.yaml` | Shelly Plus 1PM | esp32doit-devkit-v1 | HLW8012 power monitoring, relay control, esp-idf framework |
| `touch_kitchen.yaml` | Touch Kitchen | esp32dev | Capacitive touch sensor GPIO13 |

## Shared Secrets

All configs reference `secrets.yaml` using `!secret`. The secrets file contains: `wifi_ssid`, `wifi_password`, `api_encryption_key`, `ota_password`.

## Common Patterns

**Substitutions block** — used for device-specific pin assignments and names; prefer this over hardcoding values in configs.

**Standard boilerplate** every config includes: `wifi`, `api` (with encryption key), `ota`, `logger`. Most also add `captive_portal` for AP fallback.

**Home Assistant integration** — sensors/text_sensors use `platform: homeassistant` to pull HA entity state directly into the device.

**LVGL display configs** (m5dial, round_display) share the same page structure:
- `time_page` — clock + outdoor temperature
- `media_player_page` — track info + volume arc (adjustable)
- `pomodoro_page` — arc timer driven by `timer.pomodoro` HA entity

The `m5dial.yaml` version is the more complete implementation (uses `finishes_at` attribute for accurate countdown); `round_display.yaml` has a simplified stub.

## Fonts

`fonts/pixelmix.ttf` is used by the matrix display. LVGL configs load Roboto via `gfonts://Roboto`.
