CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 151;
	title = 15102;

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
				conv = 15109;
				ctype = 1;
				idx = 3142203;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 15108;
				gtype = 1;
				area = 15101;
				goal = 15104;
				grade = 132203;
				rwd = 100;
				sort = 15105;
				stype = 1;
				taid = 1;
				title = 15102;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 15108;
			gtype = 1;
			oklnk = 2;
			area = 15101;
			goal = 15104;
			sort = 15105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 15102;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 15114;
			nextlnk = 254;
			rwdtbl = 15101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7092101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 15107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3142203;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

