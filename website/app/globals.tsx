import { createGlobalState } from 'react-hooks-global-state';

let storedUsername = '';
let storedPassword = '';
let isAdmin = false;

if (typeof window !== "undefined") 
{
  storedUsername = localStorage.getItem("username") || '';
  storedPassword = localStorage.getItem("password") || '';
}

const initialState = {
  username: storedUsername,
  password: storedPassword,
  isAdmin: isAdmin,
};

const { useGlobalState, setGlobalState } = createGlobalState(initialState);

export { useGlobalState, setGlobalState };

