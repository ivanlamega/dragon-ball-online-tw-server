CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 60;
	title = 6002;

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
				conv = 6009;
				ctype = 1;
				idx = 3331201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 6008;
				gtype = 0;
				area = 6001;
				goal = 6004;
				grade = 132203;
				rwd = 100;
				sort = 6005;
				stype = 1;
				taid = 1;
				title = 6002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 6007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 3331201;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 18;
				minlvl = 10;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 6008;
			gtype = 0;
			oklnk = 2;
			area = 6001;
			goal = 6004;
			sort = 6005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 6002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 6014;
			nextlnk = 254;
			rwdtbl = 6001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3331101;
			}
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

