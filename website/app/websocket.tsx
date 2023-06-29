const address = 'ws://127.0.0.1:8820';
import React, { useEffect } from 'react';
import { useGlobalState, setGlobalState } from './globals';

let ws: WebSocket | null = null;
let isConnecting = false;

function intToBytes(num: number) 
{
  const result = [];
  result.push(num & 0xFF);
  result.push((num >> 8) & 0xFF);
  result.push((num >> 16) & 0xFF);
  result.push((num >> 24) & 0xFF);
  return result;
}

export function getJsonResponse(res: string) 
{
  const startIndex = res.indexOf('{');
  const jsonPart = res.substring(startIndex);
  return JSON.parse(jsonPart);
}

function generateCode(code: number, msgLen: number) 
{
  const codeChar = String.fromCharCode(code);
  const bytesLen = intToBytes(msgLen);
  return `${code}${bytesLen.map(byte => String.fromCharCode(byte)).join('')}`;
}

function isOpen() 
{
  if (ws != null) {
    return ws.readyState === WebSocket.OPEN;
  }
  return false;
}

export function createNewWs() {
  if (!isOpen() && !isConnecting) 
  {
    isConnecting = true;
    ws = new WebSocket(address);

    ws.onopen = () => {
      isConnecting = false;
    };

    ws.onerror = (error) => {
      console.error('WebSocket error:', error);
    };

    ws.onclose = () => 
    {
      setGlobalState('username', '');
      setGlobalState('password', '');
      localStorage.removeItem('username');
      localStorage.removeItem('password');
    };
  }
}

export function sendMsg(code: string, msg: string): Promise<string> {
  msg = `${code}{${msg}}`;

  return new Promise((resolve, reject) => 
  {
    if (isOpen()) 
    {
      ws!.send(msg);
    } 
    else 
    {
      createNewWs();
      ws!.onopen = () => {
        ws!.send(msg);
      };
    }

    ws!.onmessage = (event) => 
    {
      resolve(event.data);
    };
    

    ws!.onclose = () => 
    {
      setGlobalState('username', '');
      setGlobalState('password', '');
      localStorage.removeItem('username');
      localStorage.removeItem('password');
      reject('Connection closed');
    };
  });
}