CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 269;
	title = 26902;

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
				cont = 26908;
				gtype = 1;
				area = 26901;
				goal = 26904;
				grade = 132203;
				rwd = 100;
				sort = 26905;
				stype = 1;
				taid = 1;
				title = 26902;
			}
			CDboTSActNPCConv
			{
				conv = 26909;
				ctype = 1;
				idx = 4751201;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 26907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4751201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 12;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 26908;
			gtype = 1;
			oklnk = 2;
			area = 26901;
			goal = 26904;
			sort = 26905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 26902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 26914;
			nextlnk = 254;
			rwdtbl = 26901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511202;
			}
		}
	}
}

