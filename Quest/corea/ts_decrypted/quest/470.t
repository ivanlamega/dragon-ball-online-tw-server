CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 470;
	title = 47002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "4;4;";

			CDboTSActRegQInfo
			{
				cont = 47008;
				gtype = 0;
				area = 47001;
				goal = 47004;
				grade = 132203;
				rwd = 100;
				sort = 47005;
				stype = 2;
				taid = 1;
				title = 47002;
			}
			CDboTSActNPCConv
			{
				conv = 47009;
				ctype = 1;
				idx = 4372207;
				taid = 2;
			}
		}
		CDboTSContUnifiedNarration
		{
			cancellnk = 2;
			cid = 4;
			idx = 4702;
			lilnk = 255;
			oklnk = 2;
			prelnk = "1;";
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
			cont = 47008;
			gtype = 0;
			oklnk = 4;
			area = 47001;
			goal = 47004;
			sort = 47005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 47002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 47014;
			nextlnk = 254;
			rwdtbl = 47001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372207;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 47007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4372207;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 12;
			}
			CDboTSCheckClrQst
			{
				and = "469;";
			}
		}
	}
}

