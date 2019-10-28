CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 226;
	title = 22602;

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
				conv = 22609;
				ctype = 1;
				idx = 4511406;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 22608;
				gtype = 1;
				area = 22601;
				goal = 22604;
				grade = 132203;
				rwd = 100;
				sort = 22605;
				stype = 1;
				taid = 1;
				title = 22602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 22607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4511406;
			}
			CDboTSCheckLvl
			{
				maxlvl = 14;
				minlvl = 6;
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
			cont = 22608;
			gtype = 1;
			oklnk = 2;
			area = 22601;
			goal = 22604;
			sort = 22605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 22602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 22614;
			nextlnk = 254;
			rwdtbl = 22601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511301;
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

