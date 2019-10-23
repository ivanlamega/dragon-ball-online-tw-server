CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 432;
	title = 43202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 43208;
				gtype = 0;
				area = 43201;
				goal = 43204;
				grade = 132203;
				rwd = 100;
				sort = 43205;
				stype = 2;
				taid = 1;
				title = 43202;
			}
			CDboTSActNPCConv
			{
				conv = 43209;
				ctype = 1;
				idx = 4261101;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 43207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 15;
				minlvl = 7;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 43208;
			gtype = 0;
			oklnk = 2;
			area = 43201;
			goal = 43204;
			sort = 43205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 43202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 43214;
			nextlnk = 254;
			rwdtbl = 43201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4371312;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

