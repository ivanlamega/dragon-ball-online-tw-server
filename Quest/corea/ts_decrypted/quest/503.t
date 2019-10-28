CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 503;
	title = 50302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 50309;
				ctype = 1;
				idx = 3273101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 50308;
				gtype = 1;
				area = 50301;
				goal = 50304;
				grade = 132203;
				rwd = 100;
				sort = 50305;
				stype = 2;
				taid = 1;
				title = 50302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 50307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3273101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 23;
				minlvl = 15;
			}
			CDboTSCheckClrQst
			{
				and = "502;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 50308;
			gtype = 1;
			oklnk = 2;
			area = 50301;
			goal = 50304;
			sort = 50305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 50302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 50314;
			nextlnk = 254;
			rwdtbl = 50301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511402;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

