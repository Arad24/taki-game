import { useRouter } from "next/navigation";

const joinRoomCode = process.env.JOINROOM_CODE;
const succesCode = process.env.SUCCESS;
import { sendMsg, getJsonResponse } from '../websocket';

type Types = {
    id: number;
    name: string;
    isActive: number;
    timePerPlay: number;
    maxPlayers: number;
    currPlayers: number;
};

const Room: React.FC<Types> = ({ id, name, isActive, timePerPlay, maxPlayers, currPlayers}) => 
{
    const router = useRouter();
    
    const handleClick = () =>
    {
        joinRoom(`"roomId":${id}`).then((res) => 
        {
            if (res) router.push(`/rooms/${id}`);
        })
        .catch((error) => {
            console.error(error);
        });
    }


    return (
        <div className=' bg-white w-full py-2 rounded-lg border-black shadow-lg p-1 m-auto items-center text-center'>
            <p className={`text-white ${currPlayers == maxPlayers ? 'bg-red-500' : 'bg-green-500'} mx-40 rounded-md text-2xl mt-2 mb-2`}>{name}</p>
            <p className=' text-black font-medium text-lg mt-1'>Time Per Play: {timePerPlay}</p>
            <p className=' text-black font-medium text-lg mt-1'>Status: {(currPlayers < maxPlayers && isActive == 1) ? 'Online' : 'Ingame/Full'}</p>
            <p className=' text-black font-medium text-lg mt-1'>Players: {currPlayers}/{maxPlayers}</p>
            {(currPlayers < maxPlayers && isActive == 1) && <button 
                onClick={ handleClick }  
                className=" font-semibold border-green-500 text-green-500 border-2 px-5 py-3 rounded-lg hover:bg-green-500 transition-all duration-150 hover:text-white mt-4 ">
                Press To Join
            </button>}
            
        </div>
    );
};


async function joinRoom(msg: string)
{
    try 
    {
        const response = await sendMsg(joinRoomCode!.charAt(0), msg);
        const jsnRes = getJsonResponse(response);
        console.log(jsnRes)
        if (jsnRes.status == succesCode)
        {
            return true;
        } 
        else 
        {
            return false;
        }
    } 
    catch (error) {
        alert(error);
        return false;
    }
}

export default Room;