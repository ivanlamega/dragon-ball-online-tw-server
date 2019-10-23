CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 91;
	title = 9102;

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
				conv = 9109;
				ctype = 1;
				idx = 8032105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 9108;
				gtype = 1;
				area = 9101;
				goal = 9104;
				grade = 132203;
				rwd = 100;
				sort = 9105;
				stype = 1;
				taid = 1;
				title = 9102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 9107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 8032105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 21;
				minlvl = 13;
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
			cont = 9108;
			gtype = 1;
			oklnk = 2;
			area = 9101;
			goal = 9104;
			sort = 9105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 9102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 9114;
			nextlnk = 254;
			rwdtbl = 9101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7611201;
			}
		}
	}
}

